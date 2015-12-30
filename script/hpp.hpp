#ifndef _H_SCRIPT
#define _H_SCRIPT
									// std.includes
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#ifdef __MINGW32__
	#include <direct.h>
#else
	#include <sys/stat.h>
#endif
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
	// ----------------------------------- object evaluation
	virtual sym* eval();
	// ----------------------------------- operators
	virtual sym* at(sym*);				// A @ B = A.at(B)
	virtual sym* eq(sym*);				// A = B
	virtual sym* add(sym*);				// A + B
	virtual sym* div(sym*);				// A/B
	virtual sym* addeq(sym*);			// A += B
	// ----------------------------------- textual object dump
	std::string dump(int depth=0);		// dump object in tree form
protected:
	std::string pad(int n);				// pad dump with TABs
	virtual std::string tagval();		// return "<tag:val>"
};

									// ==== writers ===
void W(std::string);
void W(sym*);

									// === lexer/parser interface ===
extern int yylex();						// flex
extern int yylineno;
extern char* yytext;
extern int yyparse();					// bison
extern void yyerror(std::string);
#include "ypp.tab.hpp"
#define TOC(C,X) { yylval.o = new C(yytext); return X; }

extern std::map<std::string,sym*> env;				// === glob.environment ===
extern void env_init();

													// === scalar types ===
struct Sym:sym { Sym(std::string); };
struct Str:sym { Str(std::string); std::string tagval(); };
struct Hex:sym { Hex(std::string); };
struct Bin:sym { Bin(std::string); };
struct Int:sym { Int(std::string); std::string tagval(); long i; 
	Int(long); };
struct Num:sym { Num(std::string); std::string tagval(); double f; };

													// === composite types ===
struct List:sym { List(); };							// [list]
struct Vector:sym { Vector(); };						// <vector>
struct Pair:sym { Pair(sym*,sym*); };					// pa:ir
struct Tuple:sym { Tuple(); };							// tu,ple

													// === functionals ===
struct Op:sym { Op(std::string); sym*eval(); };			// operator
struct Lambda:sym { Lambda(); };						// lambda
typedef sym*(*FN)(sym*);								// function pointer
struct Fn:sym { Fn(std::string,FN); FN fn; sym*at(sym*); };// internal function
extern void fn_init();									// glob.functions

// fileio

struct Dir:sym { Dir(sym*o); sym*div(sym*); };
struct File:sym { File(std::string); File(sym*o); FILE *fh;
	sym*addeq(sym*);
	sym* write(File*);
	sym* write(Str*);
protected:
	void openR();
	void openW();
};

#define M4K 4096

#endif // _H_SCRIPT
