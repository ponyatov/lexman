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
	sym*E = env[val]; if (E) return E;				// glob. lookup
	for (auto it=nest.begin();it!=nest.end();it++)
		(*it)=(*it)->eval();
	return this;									// default: return itself
}

													// ======= operators ======
sym* sym::at(sym*o) { assert(nest.size()==1);		// default: move to nest[]ed
	push(o); return this; }		
sym* sym::eq(sym*o)	{ env[val]=o;					// env[A]=B
	if (o->tag=="^") o->val=val;					// set name to lambda
	return o; }

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

Op::Op(std::string V):sym("op",V)	{}
sym* Op::eval()						{ sym::eval();
	if (val=="@") { assert(nest.size()==2); return nest[0]->at(nest[1]); }
	if (val=="=") { assert(nest.size()==2); return nest[0]->eq(nest[1]); }
	return this;
}

Lambda::Lambda():sym("^","^") {}

Fn::Fn(std::string V,FN F):sym("fn",V)	{ fn=F; }
sym* Fn::at(sym*o)						{ return fn(o); }

// fileio

Directory::Directory(sym*o):sym("dir",o->val) {
	assert( o->tag=="str");
#ifdef __MINGW32__
	mkdir(o->val.c_str());
#else
	mkdir(o->val.c_str(),0700);
#endif
}

sym* dir(sym*o) { return new Directory(o); }

void fn_init() {
	// fileio
	env["dir"] = new Fn("dir",dir);
}

