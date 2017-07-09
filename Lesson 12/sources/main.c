#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>


#define SET_BIT(x, n) ((x) |= (0x01 << (n)))
#define RESET_BIT(x, n) ((x) &= ~(0x01 << (n)))
#define IS_BIT_SET(x, n) ((x) & (0x01 << (n)) >> (n))


static void delay_ms(uint16_t delay)
{
	while (delay--) {
		volatile uint16_t cycles = 8.656 * delay;
		while (cycles--);
	}
}

static void init_usart(const uint32_t baudrate)
{
	/*Double speed operation (U2Xn)*/
	const uint16_t ubrr = F_CPU / (8 * baudrate) - 1;

	UBRR0L = (uint8_t)(ubrr & 0xFF);
	UBRR0H = (uint8_t)((ubrr >> 8) & 0xFF);
	SET_BIT(UCSR0A, U2X0);
	SET_BIT(UCSR0B, TXEN0);

	UCSR0C = (3 << UCSZ00);
}

static size_t send_usart_message(const char mess[])
{
	size_t i = 0;
	const size_t length = strlen(mess);

	for (i = 0; i < length; ++i) {
		UDR0 = mess[i];
		while(!(UCSR0A & (1 << UDRE0)));
	}

	return length;
}

/*13 pin*/
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PORTB
#define LED_BIT 7
#define LED_OCR OCR0A
#define LED_TCCR TCCR0A
#define LED_COM COM0A1

static void init_led(void)
{
	SET_BIT(LED_DDR, LED_BIT);
}

static void init_timer(void)
{
	/*Enable counter without prescaler*/
	TCCR0B = 0x01;

	SET_BIT(LED_TCCR, LED_COM);
	SET_BIT(LED_TCCR, WGM01);
	SET_BIT(LED_TCCR, WGM00);
}

static void set_led_brightness(uint8_t bright)
{
	LED_OCR = bright;
}

/*12 pin*/
#define BUTTON_DDR DDRB
#define BUTTON_PORT PORTB
#define BUTTON_PIN PINB
#define BUTTON_BIT 6

static void init_button(void)
{
	RESET_BIT(BUTTON_DDR, BUTTON_BIT);
	SET_BIT(BUTTON_PIN, BUTTON_BIT);
}

static bool is_button_pressed(void)
{
	return (IS_BIT_SET(BUTTON_PIN, BUTTON_BIT));
}

#define SERIAL_BAUDRATE 115200

void setup(void)
{
	cli();

	init_led();
	init_usart(SERIAL_BAUDRATE);
	init_timer();

	sei();
}

void loop(void)
{
	delay_ms(50);
	volatile static uint16_t brightness = 0;

	/*send_usart_message("It works!\n\r");*/
	set_led_brightness(brightness);
	brightness += 1;
	if (brightness >= 255)
		brightness = 0;
}

int main(void)
{
	setup();
	while (1)
		loop();

	/*This point is never be reached*/
	return 0;
}
