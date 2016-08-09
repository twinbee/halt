	clr sum
	move count,d0	; load counter
loop	add d0,sum	; accumulate
	sub 1,d0	; decrement counter
	bne loop	; loop until counter is zero
	stop

word	sum
word	count = 25
