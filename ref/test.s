.name "testastos"
.comment "un test quoi"
		ld 10,r2
test1:	ldi %:live,%-2,r6
#		and r6,4026531840,r7
#		aff r7
#		aff r2
#		and r6,251658240,r7
#		aff r7
#		aff r2
#		and r6,15728640,r7
#		aff r7
#		aff r2
#		and r6,983040,r7
#		aff r7
#		aff r2
#		and r6,61440,r7
#		aff r7
#		aff r2
#		and r6,3840,r7
#		aff r7
#		aff r2
#		and r6,240,r7
#		aff r7
#		aff r2
#		and r6,15,r7
#		aff r7
#		aff r2

tampon:	sti r6,r3,r5
live:	sti r1,r5,r5
