.arch msp430g2553
.p2align 1,0

.extern BIT0
.extern BIT6

.global led_included

.global LED_RED
LED_RED: .byte BIT0

.global LED_GREEN
LED_GREEN: .byte BIT6

.global LEDS
LEDS: .byte LED_RED

.extern red_on
.extern green_on
.extern led_changed

.extern led_init
.extern led_update

.text

bis #BIT0, &LED_RED
red_on: .byte 0
green_on: .byte  0
led_changed: .byte 0
; WHY DO THESE WORK?? ^^

redVal: 
	.byte 0
	.byte LED_RED

greenVal: 
	.byte 0
	.byte LED_GREEN

led_init:
	bis &LEDS, &P1DIR
	mov #1, &led_changed
	call led_update

led_update:
	cmp 0, &led_changed
	jz no_change

  ; should be right tho...
	redValOn: .byte &red_on(redVal) ; greenVal[green_on]; keep but fix later
	greenValOn: .byte &green_on(greenVal) ; greenVal[green_on]; keep but fix later
	
	ledFlags: .byte redValOn
	bis &greenValOn, &ledFlags

  ; vv again, why does this work? why no #?
	temp: .byte 0xff
	xor &LEDS, &temp
	bis &ledFlags, &temp
	and &P1OUT, &temp

	bis &ledFlags, &P1OUT
	mov #0, &led_changed

no_change:
	ret
	