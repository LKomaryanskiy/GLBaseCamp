/*
 * Code written for Arduino Mega 2560
 * Input - PORT E4 (Pin 2)
 * Output - PROT B7 (Pin 13, LED)
 * I chose E4 port, because ports 2, 3, 18, 19, 20, 21
 * (for Arduino Mega 2560)can used for interruptions.
 */


typedef enum _LED_mode {
  blinking,
  dimming,
} LED_mode;

static const unsigned int AMOUNT_OF_MODES = 2;

/*
  Delay can be number in range 1 to 100000 ms.

  If LED mode is blinked then this
  parameter defines how much time LED will be
  turned on and turned off.

  If LED mode is dimming then this
  parameter determines how long the LED
  will go smoothly to the on / off state.
*/
static const unsigned int DELAY = 1000;
/*B7 (13 pin)*/
static const unsigned int OUTPUT_PIN = (0x01 << 7);
static const unsigned int INPUT_PIN = (0x01 << 2);
/*
   Using for the port B6 input pin register (read only).
   I use PINB instead PORTB because i can't
   read the data of PORTB.
*/
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

void next_mode(void)
{
  noInterrupts();
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    curr_mode = (((int)curr_mode) + 1) % AMOUNT_OF_MODES;
  }
  last_interrupt_time = interrupt_time;
  interrupts();
}

void ports_init(void)
{
  /*Initialize LED port (B7) for output */
  DDRB |= OUTPUT_PIN;
  /*Initialize button (E4) for input */
  DDRE &= ~(INPUT_PIN);
  //PULL-UP
  PORTE |= INPUT_PIN; 
  interrupts();
  attachInterrupt(digitalPinToInterrupt(2), next_mode, FALLING);
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
  delay_mseconds(DELAY);
  led_off();
  delay_mseconds(DELAY);
}

void dimming_mode(void)
{
  const long int blink_delay = 1000;
  static bool turned_on = true;
  static long int i = 0;
  const long int incrementer = (10 * blink_delay) / DELAY;
  led_on();
  delay_10mcseconds(blink_delay - i);
  led_off();
  delay_10mcseconds(i);
  if (turned_on)
    i += incrementer;
  else
    i -= incrementer;

  if (i >= blink_delay) {
    turned_on = false;
    i = blink_delay;
  }
  if (i <= 0) {
    turned_on = true;
    i = 0;
  }
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
