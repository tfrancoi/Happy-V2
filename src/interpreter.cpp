#include <iostream>
#include <sstream>
#include "interpreter.h"

using namespace std;

Prog* prog;
map<string, NFunction*> native;

int execute(Prog* p, string args[]) {
	initNative();
	prog = p;
	Function* main = getProgFunction("main");
	if(main == NULL) {
		cout << "No main function, no entry point for the programme, execution abort" << endl;
		return 6;
	}
	
	Env *env = new Env(main->getNbVar());
	//on met le tableau d'arg dans l'env
	
	//on appel la fonction main
	main->execute(env, NULL);
	return 0;
}

Function* getProgFunction(string name) {
	return prog->getFunction(name);
}

NFunction* getNativeFunction(string name) {
	return native[name];
}


NFunction::NFunction(Val (*f)(Env*, Store*, vector<Expression*>)) {
	this->f = f;
}

int NFunction::execute(Env* e, Store* s, vector<Expression*> args) {
	this->f(e,s,args);
	return 0;
}


Val write(Env* e, Store* s, vector<Expression*> args) {
	for(int i = 0; i < args.size(); i++) {
		Val v = args[i]->eval(s,e);
		cout << v.to_s();
		cout << " ";
	}
	cout << endl;
	
	
	return Val(1);
}

void initNative() {
	native["write"] = new NFunction(&write);
}
