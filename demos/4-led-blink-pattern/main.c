//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  // tells which bits to use as the outputs.
  P1DIR |= LEDS; // turn on both

  // acutally turns on and off the leds
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED; 

  // none of my concerns
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  // none of my concerns
  enableWDTInterrupts();	/* enable periodic interrupt */

  // make sure the cpu is listening to interrupts
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int blinkLimit = 5, blinkLimit_alt = 1; // duty cycle = 1/blinkLimit
int blinkCount = 0, blinkCount_alt = 0;  // cycles 0...blinkLimit-1
int secondCount = 0; // state var representing repeating time 0…1s

// TODO: essentially, the led blinks every x cycles,
// x changes every 1 second
// this gives us a gradient of brightness
void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking 
  blinkCount ++;
  blinkCount_alt ++;

  // when we reach the limit, reset the counter, turn on green led
  // I think this just dims the green led
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
  } else {		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN; // in any other iteration, green is off
  }

  if (blinkCount_alt >= blinkLimit_alt) {
    blinkCount_alt = 0;
    P1OUT |= LED_RED;
  } else {
    P1OUT &= ~LED_RED;
  }

  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second
    secondCount = 0;
    blinkLimit ++;	     // reduce duty cycle
    if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7.
      blinkLimit = 0;

    blinkLimit_alt --;
    if (blinkLimit_alt <= 0) // for green light, different interval
      blinkLimit_alt = 18;
  }
} 

