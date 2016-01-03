grammar ANTLRgrammar;

cal : c+ ;

c : SPC | CHAR ;

CHAR : . ;

SPC : [ \t\r\n]+ -> skip ;