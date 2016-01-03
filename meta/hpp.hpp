#ifndef _H_bI
#define _H_bI

#include <iostream>
#include <cstdlib>
using namespace std;

struct sym {
	string tag,val;
	sym(string,string);
	string dump();
};

extern void W(sym*);

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_bI
