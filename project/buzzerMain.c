#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"

int main() {
    configureClocks();
    switch_init();
    enableWDTInterrupts();

    buzzer_init();
    // buzzer_set_period(1000);	/* start buzzing!!! 2MHz/1000 = 2kHz*/
    buzzer_set_period(10000);	/* start buzzing!!! 2MHz/1000 = 2kHz*/

    or_sr(0x18);          // CPU off, GIE on
}

// 250 a second
void __interrupt_vec(WDT_VECTOR) WDT() {
    // over three seconds

    // ten levels per second, thirty levels total
    static int cycles = 0;
    // static int freq division = 10000;
    
}
