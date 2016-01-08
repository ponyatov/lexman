
syntax match  Todo		"\v\.[a-z]+[\+\-]?[ \t]*"	" .directive
syntax match  Keyword	"\v\$"						" $ inline expression
syntax match  Keyword	"\v\?"						" ? inline expression
syntax match  Identifier "\v[\{\}]"						" lambda brackets
syntax match  Keyword	"\v\@"							" lambda apply
syntax match  Keyword	"\v\%"								" member of
syntax match  Type		"\v:"								" pair/typedef
syntax match  Identifier "\~"								" lambda parameter
"syntax match  Identifier "\v\%[TFNE\%]"						" special
syntax match  Special	"\v[a-zA-Z_]+"						" symbol

syntax match  Operator	"\v[\+\-\*\/\^\@\.\,]"		" operator
