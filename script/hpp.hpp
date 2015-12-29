#ifndef _H_SCRIPT
#define _H_SCRIPT
									// std.includes
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>

									// symbolic class tree
struct sym {						// === abstract symbolic data type ===
	std::string tag;					// type/class tag
	std::string val;					// object value in string form
	sym(std::string,std::string);		// T:V constuctor
	// ----------------------------------- nested objects
	std::vector<sym*> nest;
	void push(sym*);					// push to nest[] as stack
	sym* pop();							// pop from nest[] as stack
	// ----------------------------------- parameters
	std::map<std::string,sym*> par;
	void setpar(sym*);					// set parameter
	// ----------------------------------- textual object dump
	std::string dump(int depth=0);		// dump object in tree form
protected:
	std::string pad(int n);				// pad dump with TABs
	virtual std::string tagval();		// return "<tag:val>"
};

															// scalar types
struct Sym:sym { Sym(std::string); };
struct Str:sym { Str(std::string); std::string tagval(); };
struct Hex:sym { Hex(std::string); };
struct Bin:sym { Bin(std::string); };
struct Int:sym { Int(std::string); std::string tagval(); long i; };
struct Num:sym { Num(std::string); std::string tagval(); double f; };

															// composite types
struct List:sym { List(); };
struct Vector:sym { Vector(); };
struct Pair:sym { Pair(sym*,sym*); };
															// functionals
struct Op:sym { Op(std::string); };
struct Lambda:sym { Lambda(); };

									// ==== writers ===
void W(std::string*);
void W(sym*);

									// === lexer/parser interface ===
extern int yylex();						// flex
extern int yylineno;
extern char* yytext;
extern int yyparse();					// bison
extern void yyerror(std::string);
#include "ypp.tab.hpp"
#define TOC(C,X) { yylval.o = new C(yytext); return X; }

#endif // _H_SCRIPT
