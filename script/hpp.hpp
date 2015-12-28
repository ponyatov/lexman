#ifndef _H_SCRIPT
#define _H_SCRIPT
									// std.includes
#include <iostream>
//#include <cstdlib>

									// symbolic class tree
struct sym {
	std::string tag;
	std::string val;
	sym(std::string,std::string);
	std::string dump(int depth=0);
protected:
	std::string pad(int n);
	virtual std::string tagval();
};

struct Str:sym { Str(std::string); std::string tagval(); };

									// writers
void W(std::string*);
void W(sym*);

									// lexer/parser interface
extern int yylex();						// flex
extern int yylineno;
extern char* yytext;
extern int yyparse();					// bison
extern void yyerror(std::string);
#include "ypp.tab.hpp"

#endif // _H_SCRIPT
