#include "hpp.hpp"

#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(std::string msg) { std::cout<<YYERR; std::cerr<<YYERR; exit(-1); }
int main(int argc, char *argv[]) { /*env_init();*/ return yyparse(); }

void W(std::string*s)	{ std::cout << s; }
void W(sym*o)			{ std::cout << o->dump(); }

sym::sym(std::string T,std::string V)	{ tag=T; val=V; }

std::string sym::dump(int depth) {
	std::string S = "\n"+pad(depth)+tagval();
	return S;
}

std::string sym::pad(int n)	{
	std::string S;
	for (int i=0;i<n;i++) S+="\t";
	return S;
}

std::string sym::tagval()	{ return "<"+tag+":"+val+">"; }

Str::Str(std::string V):sym("str",V)	{}
std::string Str::tagval()				{ return "<"+tag+":'"+val+"'>";}
