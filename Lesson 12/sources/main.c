#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>


#define SET_BIT(x, n) ((x) |= (0x01 << (n)))
#define RESET_BIT(x, n) ((x) &= ~(0x01 << (n)))

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

static void init_timer(void)
{
	TCCR0A |= (0x01 << 7);
}

static void init_led(void)
{
	DDRB |= (0x01 << 7);
}

static void set_led_brightness(uint8_t bright)
{
	OCR0A = bright;
}

#define SERIAL_BAUDRATE 115200

void setup(void)
{
	cli();

	init_usart(SERIAL_BAUDRATE);
	init_timer();
	init_led();

	sei();
}

void loop(void)
{
	send_usart_message("It works!\n\r");
}

int main(void)
{
	setup();
	while (1)
		loop();

	/*This point is never be reached*/
	return 0;
}
