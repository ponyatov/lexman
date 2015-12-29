#include "hpp.hpp"

#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(std::string msg) { std::cout<<YYERR; std::cerr<<YYERR; exit(-1); }
int main(int argc, char *argv[]) { env_init(); return yyparse(); }

void W(std::string s)	{ std::cout << s; }
void W(sym*o)			{ std::cout << o->dump(); }

std::map<std::string,sym*> env;						// glob.environment
void env_init() { fn_init(); }

sym::sym(std::string T,std::string V)	{ tag=T; val=V; }	// create AST object

void sym::push(sym*o)					{ nest.push_back(o); }
void sym::setpar(sym*o)					{ par[o->val]=o; }

std::string sym::pad(int n)	{ std::string S; for (int i=0;i<n;i++) S+="\t"; return S; }
std::string sym::tagval()	{ return "<"+tag+":"+val+">"; }	// header <tag:val>
std::string sym::dump(int depth) {							// dump as text tree
	std::string S = "\n"+pad(depth)+tagval();				// object header
	for (auto pr=par.begin();pr!=par.end();pr++)			// recurse par{}ams
		S += ","+pr->first+"_"+pr->second->tagval();
	for (auto it=nest.begin();it!=nest.end();it++)			// recurse nest[]ed
		S += (*it)->dump(depth+1);
	return S;
}

sym* sym::eval() {											// eval/compute
	sym*E = env[val]; if (E) return E;	// glob. lookup
	return this;						// default: return itself
}

															// operators
sym* sym::at(sym*o) { push(o); }		// default: move to nest[]ed

Sym::Sym(std::string V):sym("sym",V)	{}

Str::Str(std::string V):sym("str",V)	{}
std::string Str::tagval()				{ return "<"+tag+":'"+val+"'>";}

Hex::Hex(std::string V):sym("hex",V)	{}
Bin::Bin(std::string V):sym("bin",V)	{}

Int::Int(std::string V):sym("int","")	{ i = atoi(V.c_str()); }
std::string Int::tagval() {
	std::ostringstream os; os<<"<"<<tag<<":"<< i <<">"; return os.str(); }

Num::Num(std::string V):sym("num","")	{ f = atof(V.c_str()); }
std::string Num::tagval() {
	std::ostringstream os; os<<"<"<<tag<<":"<< f <<">"; return os.str(); }

List::List():sym("[","]") {}
Vector::Vector():sym("","") {}
Pair::Pair(sym*A,sym*B):sym(A->val,B->val) { push(A); push(B); }

Op::Op(std::string V):sym("op",V) {}
Lambda::Lambda():sym("^","^") {}

void fn_init() {}

