#ifndef _H_bI
#define _H_bI

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <map>
#ifdef __MINGW32__
	#include <direct.h>
#else
#endif
using namespace std;

struct sym {								////// dynamic symbol type
	string tag,val;							// <tag:val> object repr
	sym(string,string);
	virtual string dump(int depth=0);		// \ dumping 
	virtual string tagval();
	string pad(int);						// /
	vector<sym*> nest;						// \ nested objects list
	void push(sym*);						// /
	virtual sym* eval();					// compute/evaluate object
	virtual sym* eq(sym*);					// \\ operators
	virtual sym* at(sym*);
};

extern map<string,sym*> env;				//////////// environment
extern void env_init();
											//////////// scalars
struct Sym:sym { Sym(string); };			// symbol
struct Str:sym { Str(string); 				// string
	string tagval(); };

struct Int:sym { Int(string); long i; };	// integer

											//////////// functionals
struct Op:sym { Op(string); sym*eval(); };	// operator
typedef sym*(*FN)(sym*);					// fn ptr
struct Fn:sym { Fn(string,FN); FN fn; 		// function
	sym*at(sym*); };

											//////////// fileio
struct Dir:sym { Dir(sym*); };				// dir constructor
extern sym* dir(sym*);
struct File:sym { File(sym*); };			// file constructor
extern sym* file(sym*);

extern void W(sym*);
extern void W(string);

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"
#define TOC(C,X) { yylval.o = new C(yytext); return X; }

#endif // _H_bI
