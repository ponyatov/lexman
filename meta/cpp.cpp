#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

void W(sym*o)		{ cout << o->dump(); }				// \ writers
void W(string s)	{ cout << s; }						// /

/////////////////// sym ////////////////////

sym::sym(string T,string V)	{ tag=T; val=V; }
void sym::push(sym*o)		{ nest.push_back(o); }
sym* sym::eval()			{
	if (env[val]) return env[val];
	for (auto it=nest.begin();it!=nest.end();it++)
		(*it) = (*it)->eval();
	return this; }

string sym::pad(int n)		{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }
string sym::tagval()		{ return "<"+tag+":"+val+">"; }
string sym::dump(int depth)	{ string S = "\n"+pad(depth)+tagval();
	for (auto pr=par.begin();pr!=par.end();pr++)
		S+=","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin();it!=nest.end();it++)
		S+=(*it)->dump(depth+1);
	return S; }

sym* sym::eq(sym*o)			{ env[val]=o; return o; }	// =
sym* sym::comma(sym*o)		{ par[o->val]=o; return this; } // ,
sym* sym::at(sym*o)			{ return new Op("@@",this,o); }	// @
sym* sym::div(sym*o)		{ return new Op("//",this,o); }	// /

//////////////////// scalars /////////////////////

Sym::Sym(string V):sym("sym",V) {}
Str::Str(string V):sym("str",V) {}
string Str::tagval()			{ return "<"+tag+":'"+val+"'>"; }

Int::Int(string V):sym("int",V) { i = atoi(val.c_str()); }

//////////////////// functionals ////////////////

Op::Op(string V):sym("op",V)				{}
Op::Op(string V,sym*A,sym*B):sym("op",V)	{ push(A); push(B); }
sym* Op::eval() {
	sym::eval();
	if (nest.size()==2) {
		if (val=="=") return nest[0]->eq(nest[1]);
		if (val=="@") return nest[0]->at(nest[1]);
		if (val==",") return nest[0]->comma(nest[1]);
		if (val=="/") return nest[0]->div(nest[1]);
	}
	return this;
}

Fn::Fn(string V,FN F):sym("fn",V)	{ fn=F; }
sym* Fn::at(sym*o)					{ return fn(o); }

///////////////////// fileio ////////////////////

Dir::Dir(sym*o):sym("dir",o->val) { mkdir(o->val.c_str()); }

sym* Dir::div(sym*o)	{ return new File(this,o); }

sym* dir(sym*o)		{ return new Dir(o); }

File::File(Dir*D,sym*o):sym("file",D->val+'/'+o->val) {
	if (o->par["W"]) {
		par["mode"]=o->par["W"]; assert(fh=fopen(val.c_str(),"w"));
	} else {
		par["mode"]=o->par["R"]; assert(fh=fopen(val.c_str(),"r"));
	}
}

map<string,sym*> env;
void env_init(){
	env["dir"] = new Fn("dir",dir);
}
