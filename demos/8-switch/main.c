#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

// vv normal behavior
void main(void) 
{  
  configureClocks();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);  // CPU off, GIE on
} 

void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

/* up=red, down=green */
  if (p1val & SW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}
// ^^

// vv uncomment for toggle behavior
// void main(void) 
// {  
//   configureClocks();

//   P1DIR |= LEDS;
//   P1OUT &= ~LEDS;		/* leds initially off */
  
//   P1REN |= SWITCHES;		/* enables resistors for switches */
//   P1IE |= SWITCHES;		/* enable interrupts from switches */
//   P1OUT |= SWITCHES;		/* pull-ups for switches */
//   P1DIR &= ~SWITCHES;		/* set switches' bits for input */
//   P1IES |= SWITCHES; // always rising edge
//   // remember: you don't set equal; you |=

//   or_sr(0x18);  // CPU off, GIE on
// } 

// void
// switch_interrupt_handler()
// {
//   // if led green on, turn off, turn red on
//   if (P1OUT & LED_GREEN) {
//     P1OUT &= ~LED_GREEN;
//     P1OUT |= LED_RED;
//   } else { // otherwise, red off, green on
//     P1OUT &= ~LED_RED;
//     P1OUT |= LED_GREEN;
//   }
// }
// ^^

// vv uncomment for timer behavior
// // state variables for timer
// int cycles = 0;
// int delay = 250; // 1 second

// void main(void) 
// {  
//   configureClocks();
//   enableWDTInterrupts();

//   P1DIR |= LEDS;
//   P1OUT &= ~LEDS;		/* leds initially off */
  
//   P1REN |= SWITCHES;		/* enables resistors for switches */
//   P1IE |= SWITCHES;		/* enable interrupts from switches */
//   P1OUT |= SWITCHES;		/* pull-ups for switches */
//   P1DIR &= ~SWITCHES;		/* set switches' bits for input */
//   P1IES |= SWITCHES; // always rising edge
//   // remember: you don't set equal; you |=

//   or_sr(0x18);  // CPU off, GIE on
// } 

// void
// switch_interrupt_handler()
// {
//   // reset time counter
//   cycles = 0;

//   // turn green off, turn red on
//   P1OUT &= ~LED_GREEN;
//   P1OUT |= LED_RED;

//   // this will reset to green after one second
// }

// void
// __interrupt_vec(WDT_VECTOR) WDT() {
//   cycles++;
  
//   // if one second has passed, switch to green
//   if (cycles > delay) {
//     P1OUT &= ~LED_RED;
//     P1OUT |= LED_GREEN;
//   }
// }
// ^^

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
