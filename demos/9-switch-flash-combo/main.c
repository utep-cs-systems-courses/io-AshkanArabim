#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED | LED_GREEN)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

// global state variable
int state = 0;

void switch_init() {
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
  P1IES |= SWITCHES;
}

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
}

void wdt_init() {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
}

void main(void) 
{  
  switch_init();
  led_init();
  wdt_init();
    
  or_sr(0x18);  // CPU off, GIE on
} 

static int buttonDown;

void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */

  state++;
  if (state >= 5) {
    // DEBUG
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;

    state = 0;
  }
}

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  static int blink_count = 0; // value retained because it's static
  blink_count++;

  switch (state)
  {
  case 0: // both on
    P1OUT |= LEDS;
    break;

  case 1: // green on 
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;

  case 2: // red on
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    break;

  case 3: // alternating red and green
    if (blink_count < 125) {
      // for half a second red is on
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
    } else {
      // for half a second green is on
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    }
    break;

  case 4: // all off
    P1OUT &= ~LEDS;
    break;
  
  default:
    P1OUT &= ~LEDS;
    state = 0;
    break;
  }

  if (blink_count > 250) { // I don't care about more than 1 sec.
    blink_count = 0;
  }

  // switch (blink_count) { 
  // case 6: 
  //   blink_count = 0;
  //   P1OUT |= LED_RED;
  //   break;
  // default:
  //   blink_count ++;
  //   if (!buttonDown) P1OUT &= ~LED_RED; /* don't blink off if button is down */
  // }
} 
