#ifndef _H_bI
#define _H_bI

#include <iostream>
#include <cstdlib>
#include <cstdio>
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
	map<string,sym*> par;					// parameters
	virtual sym* eval();					// compute/evaluate object
											// \ operators
	virtual sym* eq(sym*);					// =
	virtual sym* at(sym*);					// @
	virtual sym* comma(sym*);				// ,
	virtual sym* div(sym*);					// /
};

extern map<string,sym*> env;				//////////// environment
extern void env_init();
											//////////// scalars
struct Sym:sym { Sym(string); };			// symbol
struct Str:sym { Str(string); 				// string
	string tagval(); };

struct Int:sym { Int(string); long i; };	// integer

											//////////// functionals
struct Op:sym { Op(string); sym*eval(); 	// operator
	Op(string,sym*,sym*); };
typedef sym*(*FN)(sym*);					// fn ptr
struct Fn:sym { Fn(string,FN); FN fn; 		// function
	sym*at(sym*); };

											//////////// fileio
struct Dir:sym { Dir(sym*); 				// dir constructor
	sym*div(sym*); };
extern sym* dir(sym*);
struct File:sym { File(sym*); File(Dir*,sym*); FILE *fh; }; // file constructor
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
