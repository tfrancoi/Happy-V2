#include <iostream>
#include <sstream>
#include "interpreter.h"
#include "lib/standard.h"
#include "lib/reference.h"

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
	Store* s = new Store();
	//on met le tableau d'arg dans l'env
	
	//on appel la fonction main
	main->execute(env, s);
	return 0;
}

Function* getProgFunction(string name) {
	return prog->getFunction(name);
}

NFunction* getNativeFunction(string name) {
	return native[name];
}


NFunction::NFunction(Val (*f)(Env*, Store*, vector<Expression*>, int line, string file)) {
	this->f = f;
}

Val NFunction::eval(Store* s, Env* e, vector<Expression*> args, int line, string file) {
	return this->f(e,s,args,line,file);
}


void initNative() {
	init_arithmetic(native);
	init_io(native);		
	init_reference(native);	
}

void runtime_error(string msg, int line, string file) {
	cout << msg << endl;
	cout << "\t at line " << line << " in file " << file << endl;
}
