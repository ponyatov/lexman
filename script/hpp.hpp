#ifndef _H_SCRIPT
#define _H_SCRIPT
									// std.includes
#include <iostream>
#include <sstream>
#include <cstdlib>

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
															// scalar types
struct Sym:sym { Sym(std::string); };
struct Str:sym { Str(std::string); std::string tagval(); };
struct Hex:sym { Hex(std::string); };
struct Bin:sym { Bin(std::string); };
struct Int:sym { Int(std::string); std::string tagval(); long i; };
struct Num:sym { Num(std::string); std::string tagval(); double f; };

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
#define TOC(C,X) { yylval.o = new C(yytext); return X; }

#endif // _H_SCRIPT
