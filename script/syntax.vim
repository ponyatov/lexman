" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/lexman/script
syntax match  Comment	"\v#.*"						" # line comment
syntax region Comment	start="#|" end="|#"			" #| block comment |#
syntax match  Constant	"\v[0-9]+"					" number
syntax region String	start="'" end="'"			" 'string'
syntax match  Type		"\v[\[\]\(\)\<\>\{\}\:\=]"	" bracket
syntax match  Operator	"\v[\+\-\*\/\^\@\.\,]"		" operator
