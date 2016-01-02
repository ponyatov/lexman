grammar ANTLRgrammar;

calc : expr+ ;
expr : scalar ;
num : INT | HEX | BIN ;
scalar : num | ID ;

COMMENT : '#'[^\n]* ;

INT :   ('0'..'9')+ ;
HEX :   '0x'[0-9A-F]+ ;
BIN :   '0b'[01]+ ;
ID  :   [a-zA-Z_][a-zA-Z_0-9]* ;

SPACE : [ \t\r\n]+ ;
