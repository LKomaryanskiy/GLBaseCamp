/*
 * Code written for Arduino Mega 2560
 */


typedef enum _LED_mode {
  blinking,
  dimming,
  AMOUNT_OF_MODES,
} LED_mode;

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
static unsigned int led_delay = 1000;
/*Min and max value of led delay*/
static const unsigned int led_delay_max = 10000;
static const unsigned int led_delay_min = 25;
/*B7 (13 pin)*/
static const unsigned int OUTPUT_PIN = (0x01 << 7);
/*E4 (2 pin)*/
static const unsigned int INPUT_PIN = (0x01 << 2);
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

/*TODO: Change this function to avr interruption vector*/
void next_mode(void)
{
  /*TODO: Fix - save previous SREG state*/
  noInterrupts();
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) {
    curr_mode = (LED_mode)((curr_mode + 1) % AMOUNT_OF_MODES);
  }
  last_interrupt_time = interrupt_time;
  /*TODO: Restore SREG state*/
}

void ports_init(void)
{
  /*Initialize LED port (B7) for output */
  DDRB |= OUTPUT_PIN;
  /*Initialize button (E4) for input */
  DDRE &= ~(INPUT_PIN);
  //PULL-UP
  PORTE |= INPUT_PIN; 
  /*TODO: Add interruptions execution*/
}

void led_on(void)
{
  PORTB |= OUTPUT_PIN;
}

void led_off(void)
{
  PORTB &= (~OUTPUT_PIN);
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
  /*TODO: Rewrite using PWM*/
}

void setup(void)
{
  Serial.begin(115200);
  ports_init();
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
