/*
 * Code written for Arduino Mega 2560.
 * Output: LED (B7 13 pin).
 * Input: Button (B6 12 pin)
 *        EncoderB (B5 11 pin)
 *        EncoderA (B4 10 pin).
 * 
 * For changing frequency of blinking\dimming,
 * use rotate encoder. For changing LED mode 
 * press button.
 */


typedef enum _LED_mode {
  blinking,
  dimming,
  AMOUNT_OF_MODES,
} LED_mode;

static const unsigned int DELAY_BETWEEN_INTERRUPTS = 10;
/*Min and max value of led delay.*/
static const unsigned int LED_DELAY_MAX = 1000;
static const unsigned int LED_DELAY_MIN = 100;
/*
  Delay can be number in range 1 to 100000 ms.

  If LED mode is blinked then this
  parameter defines how much time LED will be
  turned on and turned off.

  If LED mode is dimming then this
  parameter determines how long the LED
  will go smoothly to the on / off state.

  led_delay can be changed using rotation encoder. 
*/
static unsigned int led_delay = LED_DELAY_MAX;
/*I use the model of encoder that has 20 states per lap.*/
static const unsigned int ONE_LAP = 20;
/*Amount of laps, needed to setting minimum delay.*/
static const unsigned int AMOUNT_OF_LAPS = 1;

static unsigned int curr_encoder_stat = 0;

/*B7 (13 pin).*/
static const unsigned int OUTPUT_PIN = (0x01 << 7);
/*B6 (12 pin).*/
static const unsigned int BUTTON_PIN = (0x01 << 6);
/*B4 (10 pin).*/
static const unsigned int ROTB_PIN = (0x01 << 5);
/*B5 (11 pin).*/
static const unsigned int ROTA_PIN = (0x01 << 4);
/*Describes all input signals - button and 2 signals from encoder.*/
static const unsigned int INPUT_PINS = BUTTON_PIN | ROTB_PIN | ROTA_PIN;

static LED_mode curr_mode = blinking;

void delay_10mcseconds(unsigned int delay_mcs)
{
  volatile unsigned int cycles = 8.656 * delay_mcs;
  while (cycles > 0) {
    --cycles;
  }
}

void delay_mseconds(unsigned int delay_ms)
{
  while (delay_ms--)
    delay_10mcseconds(100);
}

void timer_init(void)
{
  TCCR0A |= (0x01 << 7);
}

void enable_interruptions(void)
{
  SREG |= (0x01 << 7);
}

void disable_interruptions(void)
{
  SREG &= ~(0x01 << 7);
}

void ports_init(void)
{
  DDRB |= OUTPUT_PIN;
  
  PCICR |= 0x01;
  PCMSK0|= INPUT_PINS;
  DDRB |= INPUT_PINS;
  PORTB |= INPUT_PINS;
  enable_interruptions();
}

void button(void)
{
  curr_mode = (LED_mode)((curr_mode + 1) % AMOUNT_OF_MODES);
}

void recalculate_delay(void)
{
  led_delay = LED_DELAY_MAX - (curr_encoder_stat) * \
  ((LED_DELAY_MAX - LED_DELAY_MIN) / (AMOUNT_OF_LAPS * ONE_LAP));
}

void reduce_delay(void)
{
  if (curr_encoder_stat > 0)
    --curr_encoder_stat;
  recalculate_delay();
}

void increase_delay(void)
{
  if (curr_encoder_stat < AMOUNT_OF_LAPS * ONE_LAP)
    ++curr_encoder_stat;
  recalculate_delay();
}

ISR(PCINT0_vect)
{
  unsigned int save_SREG = SREG;
  disable_interruptions();
  static unsigned long int last_interrupt_time = 0;
  unsigned long int interrupt_time = millis();
  /* If interrupts come faster than DELAY_BETWEEN_INTERRUPTS ms, assume it's a bounce and ignore.*/
  if (interrupt_time - last_interrupt_time > DELAY_BETWEEN_INTERRUPTS) {
    static unsigned int pins_last_status = 0;
    unsigned int pins_curr_status = ~PINB & (INPUT_PINS);
    switch (pins_last_status ^ pins_curr_status) {
      case BUTTON_PIN: {
        button();
        break;
      }
      case ROTA_PIN:{
        reduce_delay();
        break;
      }
      case ROTB_PIN: {
        increase_delay();
        break;
      }
      default:
        break;
    }
  }
  last_interrupt_time = interrupt_time;
  SREG = save_SREG;
}

/*Value can be number in range 0 to 255.*/
void analog_write_LED(int value)
{
  OCR0A = value;
}

void led_on(void)
{
  analog_write_LED(0x00);
}

void led_off(void)
{
  analog_write_LED(0xFF);
}

void blinking_mode(void)
{
  led_on();
  delay_mseconds(led_delay);
  led_off();
  delay_mseconds(led_delay);
}

void dimming_mode(void)
{
  static int dimm_amount = 5;
  unsigned int inside_delay = ((dimm_amount < 0 ? -dimm_amount : dimm_amount) * \
            led_delay) / 255; 
  
  static int value = 0;
  value += dimm_amount;
  if (value >= 255 || value <= 0) 
    dimm_amount =-dimm_amount;
  
  analog_write_LED(value);
  delay_mseconds(inside_delay);
}

void setup(void)
{
  ports_init();
  timer_init();
}

void loop(void)
{
  /*I use switch state for adding new state more simply.*/
  switch (curr_mode) {
    case blinking: {
        blinking_mode();
        break;
      }
    case dimming: {
        dimming_mode();
        break;
      }
    default :
      break;
  }
}
