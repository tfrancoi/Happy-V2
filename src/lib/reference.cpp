#include <iostream>
#include <cstdlib>
#include "../interpreter.h"
#include "standard.h"
#include "reference.h"

using namespace std;

void init_reference(map<string, NFunction*> &native) {
	native["new"] = new NFunction(&::into_store);
	native["@"] = new NFunction(&::get_into_store);
	native[":="] = new NFunction(&::change_into_store);
}

Val rtov(Val v, Store* s) {
	if(v.getType() == REFERENCE) {
		return s->getVal(v.get_ref());
	}
	return v;
}


Val into_store(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() > 2) {
		cout << "new take max one argument" << endl;
		exit(1);
	}
	Val val;
	if(args.size()) {
		val = args[0]->eval(s,e);
	}
	else {
		val = Val();
	}
	unsigned int ref = s->newVal(val);
	
	Val v = Val(ref);
	//cout << "new ref " << v.get_ref() << endl;
	return v;	
}

Val change_into_store(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 2) {
		cout << ":= take exactly two arguments" << endl;
		exit(1);
	}
	Val v1 = args[0]->eval(s,e);
	if(v1.getType() != REFERENCE) {
		cout << ":= need a 	reference as first argument" << endl;
		exit(1);
	}
	int ref = v1.get_ref();
	s->setVal(args[1]->eval(s,e), ref);
	return v1;	
}



Val get_into_store(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 1) {
		cout << "@ take only one argument" << endl;
		exit(1);
	}
	Val v1 = args[0]->eval(s,e);
	if(v1.getType() != REFERENCE) {
		cout << "@ take only ref argument" << endl;
		exit(1);
	}
	return s->getVal(v1.get_ref());	
}
