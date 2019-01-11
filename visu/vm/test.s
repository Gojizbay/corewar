.name "coucou"
.comment "comment ca va"

debut:
		ld	%1006632960,r2
		sti	r2,%:test,%1
		ld	%0,r2
		sti	r2,%:test3,%1
test:	ld %1,r6
test2:	ld %1,r7
test3:	ld %1,r9
aff:	aff r6
		aff r7
		aff r9
