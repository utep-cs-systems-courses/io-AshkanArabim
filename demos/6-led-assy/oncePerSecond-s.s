	.arch msp430g2553
	; align to 16 bits with no fill ptrn
	.p2align 1,0

.data
	; accessible from other files
	.global oncePerSecond
	.extern P1OUT
	.extern blinkLimit

.text
oncePerSecond:
	add #1, &blinkLimit
	; vv second operand can't be a constant
	cmp #8, &blinkLimit ;this may be in reverse
	jge valid
	pop r0 ; return - pop from stack
valid: 
	mov #0, &blinkLimit
	pop r0

; oncePerSecond:
;     ; Increment the value at the memory location 'blinkLimit'
;     mov.w &blinkLimit, R12      ; Load blinkLimit into R12
;     inc.w R12                   ; Increment R12
;     mov.w R12, &blinkLimit      ; Store R12 back into blinkLimit

;     ; Compare 'blinkLimit' with 8 and reset to 0 if greater or equal
;     mov.w &blinkLimit, R13      ; Load blinkLimit into R13
;     cmp.w #8, R13               ; Compare R13 with 8
;     jge valid                   ; Jump to 'valid' if R13 is greater than or equal to 8
;     jmp end                     ; Jump to 'end' if the condition is not met

; valid:
;     mov.w #0, &blinkLimit       ; Set blinkLimit to 0

; end:
;     ret

; SIMPLIFIED
; oncePerSecond:
;     ; Increment the value at the memory location 'blinkLimit'
;     ; mov.w &blinkLimit, R12      ; Load blinkLimit into R12
;     inc.w &blinkLimit                   ; Increment R12
;     ; mov.w R12, &blinkLimit      ; Store R12 back into blinkLimit

;     ; Compare 'blinkLimit' with 8 and reset to 0 if greater or equal
;     ; mov.w &blinkLimit, R13      ; Load blinkLimit into R13
;     cmp.w #8, &blinkLimit               ; Compare R13 with 8
;     jge valid                   ; Jump to 'valid' if R13 is greater than or equal to 8
;     jmp end                     ; Jump to 'end' if the condition is not met

; valid:
;     mov.w #0, &blinkLimit       ; Set blinkLimit to 0

; end:
; 		pop r0


; EXTRA SIMPLIFIED
; oncePerSecond:
;     ; Increment the value at the memory location 'blinkLimit'
;     ; mov &blinkLimit, R12      ; Load blinkLimit into R12
;     add #1, &blinkLimit                   ; Increment R12
;     ; mov R12, &blinkLimit      ; Store R12 back into blinkLimit

;     ; Compare 'blinkLimit' with 8 and reset to 0 if greater or equal
;     ; mov &blinkLimit, R13      ; Load blinkLimit into R13
;     cmp #8, &blinkLimit               ; Compare R13 with 8
;     jge valid                   ; Jump to 'valid' if R13 is greater than or equal to 8
;     jmp end                     ; Jump to 'end' if the condition is not met

; valid:
;     mov #0, &blinkLimit       ; Set blinkLimit to 0

; end:
; 		pop r0
