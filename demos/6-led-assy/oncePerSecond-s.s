	.arch msp430g2553
	; align to 16 bits with no fill ptrn
	.p2align 1,0

	; accessible from other files
	.global oncePerSecond
	.extern P1OUT
	.extern blinkLimit

oncePerSecond:
	;; blinkLimit ++
	add #1 &blinkLimit
	;; if (blinkLimit >= 8) blinkLimit = 0
temp:	 
	JL 
end:	
