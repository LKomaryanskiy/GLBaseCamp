#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>

/*Set bit*/
#define sbi(x, n) ((x) |= (0x01 << (n)))
/*Clean bit*/
#define cbi(x, n) ((x) &= ~(0x01 << (n)))

static void delay_ms(uint16_t delay)
{
	while (delay--) {
		volatile uint16_t cycles = 8.656 * delay;
		while (cycles--);
	}
}

/*Instruments for USART*/
#define USART_BUFFER_SIZE 256
static char usart_buffer[USART_BUFFER_SIZE];
static uint16_t usart_curr_message_length = 0;
static uint16_t usart_curr_buf_index = 0;

static void enable_tx_usart_interrupt(void)
{
	sbi(UCSR0B, TXCIE0);
}

static void disable_tx_uasrt_interrupt(void)
{
	cbi(UCSR0B, TXCIE0);
}

static void init_usart(const uint32_t baudrate)
{
	/*Double speed operation (U2Xn)*/
	const uint16_t ubrr = F_CPU / (8 * baudrate) - 1;

	UBRR0L = (uint8_t)(ubrr & 0xFF);
	UBRR0H = (uint8_t)((ubrr >> 8) & 0xFF);
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	disable_tx_uasrt_interrupt();

	UCSR0C = (3 << UCSZ00);
}

/*DEBUG*/
static void print_polling(const char mess[])
{
	size_t i = 0;
	size_t N = strlen(mess);
	for (i = 0; i < N; ++i){
		UDR0 = mess[i];
		while (!(UCSR0A & (1 << UDRE0)));
	}
}

static void send_usart_symbol()
{
	UDR0 = usart_buffer[usart_curr_buf_index];
	++usart_curr_buf_index;
	usart_curr_buf_index = (usart_curr_buf_index) % \
								USART_BUFFER_SIZE;
	--usart_curr_message_length;
}

static void send_usart_message(const char mess[])
{
	/*
	 *	Copy message to cyclic buffer and then enable interrupts.
	 *	Mod of USART_BUFFER_SIZE prevents buffer overflowing.
	 */
	//print_polling("SENDING MESSAGE!\n\r");
	disable_tx_uasrt_interrupt();
	const size_t length = (strlen(mess)) % (USART_BUFFER_SIZE - \
			usart_curr_message_length);
	size_t i = 0;
	for (i = 0; i < length; ++i){
		size_t index = (usart_curr_buf_index + i) % USART_BUFFER_SIZE;
		usart_buffer[index] = mess[i];
	}
	usart_curr_message_length += length;
	enable_tx_usart_interrupt();
	send_usart_symbol();
}

ISR(USART0_TX_vect)
{
	send_usart_symbol();
	if (usart_curr_message_length)
		enable_tx_usart_interrupt();
	else
		disable_tx_uasrt_interrupt();
}

/*LED & timer*/
/*13 pin*/
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PORTB
#define LED_BIT 7
#define LED_OCR OCR0A
#define LED_TCCR TCCR0A
#define LED_COM COM0A1

static uint8_t led_bright = 0;
static bool led_is_enabled = true;

static void init_led(void)
{
	sbi(LED_DDR, LED_BIT);
}

static void init_timer(void)
{
	/*Enable counter from prescaler clk/64*/
	TCCR0B = 0x03;

	sbi(LED_TCCR, LED_COM);
	sbi(LED_TCCR, WGM01);
	sbi(LED_TCCR, WGM00);
}

static void set_led_brightness(uint8_t bright)
{
	if (led_is_enabled)
		LED_OCR = bright;
	else
		LED_OCR = 0x00;
}

/*Encoder*/
/*12 pin*/
#define ENCODER_DDR DDRB
#define ENCODER_PORT PORTB
#define ENCODER_PIN PINB
#define ROTA_BIT 4
#define ROTB_BIT 5
#define BUTTON_BIT 6
#define ENCODER_PCIE 1
#define ENCODER_PCMSK PCMSK0
#define ENCODER_PCINT_vect PCINT0_vect

/*Encoder parameter*/
static const uint16_t ONE_LAP = 40;
static uint8_t encoder_curr_state = 0;

static void init_encoder(void)
{
	PCICR = ENCODER_PCIE;
	sbi(ENCODER_PCMSK, ROTA_BIT);
	sbi(ENCODER_PCMSK, ROTB_BIT);
	sbi(ENCODER_PCMSK, BUTTON_BIT);

	cbi(ENCODER_DDR, ROTA_BIT);
	cbi(ENCODER_DDR, ROTB_BIT);
	cbi(ENCODER_DDR, BUTTON_BIT);

	sbi(ENCODER_PIN, ROTA_BIT);
	sbi(ENCODER_PIN, ROTB_BIT);
	sbi(ENCODER_PIN, BUTTON_BIT);
}

static void recalculate_bright(void)
{
	led_bright = encoder_curr_state * (255 / ONE_LAP);
}

static void reduce_bright(void)
{
	if (encoder_curr_state > 0)
		--encoder_curr_state;
	recalculate_bright();
}

static void increase_bright(void)
{
	if (encoder_curr_state <= ONE_LAP)
		++encoder_curr_state;
	recalculate_bright();
}

static void button(void)
{
	static bool prev_state_pressed = false;
	if (prev_state_pressed)
		led_is_enabled = !led_is_enabled;
	prev_state_pressed = !prev_state_pressed;
}

ISR(ENCODER_PCINT_vect)
{
	static bool is_rot = true;
	uint8_t save_SREG = SREG;
	static uint8_t pins_prev_status = 0;
	const uint8_t input_pin_mask = (0x01 << ROTA_BIT) | \
			(0x01 << ROTB_BIT) | (0x01 << BUTTON_BIT);
	uint8_t pins_curr_status = ~ENCODER_PIN & input_pin_mask;

	switch (pins_prev_status ^ pins_curr_status){
		case (0x01 << ROTA_BIT): {
			if (is_rot)
				increase_bright();
			is_rot = !is_rot;
			break;
		}
		case (0x01 << ROTB_BIT): {
			if (is_rot)
				reduce_bright();
			is_rot = !is_rot;
			break;
		}
		case (0x01 << BUTTON_BIT): {
			button();
			break;
		}
		default:
			break;
	}

	pins_prev_status = pins_curr_status;
	SREG = save_SREG;
}


#define SERIAL_BAUDRATE 115200

void setup(void)
{
	cli();

	init_led();
	init_usart(SERIAL_BAUDRATE);
	init_timer();
	init_encoder();

	sei();
}

void loop(void)
{
	delay_ms(200);
	send_usart_message("It works!\n\r");
	set_led_brightness(led_bright);
}

int main(void)
{
	setup();
	while (1)
		loop();

	/*This point is never be reached*/
	return 0;
}
