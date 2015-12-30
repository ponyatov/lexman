# comment
[								# \ outer list
< -01 00 +02 0x12AF:0b1101 >	# < integers, hex : binary > vector, pa:ir 
[ -01.20 -03e+04 ]				# [ float numbers ] nested list
'string'
[ symbol ctype:string ]
[ {} {X:} {Y:Y} {X:Y: X+Y*A^B}	# lambdas
]
]								# / outer list

# fileio
next = dir@'next'				# create dir apply with @ operator
make = next/Makefile@W
make += Makefile
make += file@'lpp.lpp'

#Makefile@R

#make = file(next/Makefile)		# create file (apply in C-like form with parens)
								# create lex.program using functional expression
								#   multi assignment and string % templating
#ypp,lpp,hpp,cpp = map(file,
#	{X:'%s.%s'%(X,X)}@
#		['ypp','lpp','hpp','cpp']
#	)
#next.ls							# file list via . operator 
