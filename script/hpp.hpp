#ifndef _H_SCRIPT
#define _H_SCRIPT
									// std.includes
#include <iostream>
//#include <cstdlib>

									// symbolic class tree
class sym {
public:
	std::string tag;
	std::string val;
	sym(std::string,std::string);
	std::string dump(int depth=0);
protected:
	std::string pad(int n);
	std::string tagval();
};

									// writers
void W(std::string*);
void W(sym*);

									// lexer/parser interface
extern int yylex();						// flex
extern int yylineno;
extern char* yytext;
extern int yyparse();					// bison
extern void yyerror(std::string);

#endif // _H_SCRIPT
