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
	native["array"] = new NFunction(&::array);
	native["<<"] = new NFunction(&::append);
	native["#"] = new NFunction(&::get_index);
	native["len"] = new NFunction(&::len);
	native["list"] = new NFunction(&::list);
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

Val array(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 0) {
		cout << "Array take no argument" << endl;
		exit(1);
	}
	Val val = Val(new vector<Val>());	
	unsigned int ref = s->newVal(val);
	Val v = Val(ref);
	return val;
	
}

Val append(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() < 1) {
		cout << "<< take at least two argument" << endl;
		exit(1);
	}
	Val ref = args[0]->eval(s,e);
	Val tab = rtov(ref, s);
	if(tab.getType() != ARRAY) {
		cout << "<< take as first argument an array" << endl;
		exit(1);
	}
	vector<Val>* array = tab.to_array();
	
	for(unsigned int i = 1; i < args.size(); i++) {
		array->push_back(args[i]->eval(s,e));
	}
	return ref;	
}

Val get_index(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 2 && args.size() != 3 ) {
		cout << "# take two or tree argument" << endl;
		exit(1);
	}
	Val ref = args[0]->eval(s,e);
	Val tab = rtov(ref, s);
	if(tab.getType() != ARRAY) {
		cout << "# take as first argument an array" << endl;
		exit(1);
	}
	Val i = rtov(args[1]->eval(s,e), s);
	if(i.getType() != INTEGER) {
		cout << "# take as second argument an integer" << endl;
		exit(1);
	}
	vector<Val>* array = tab.to_array();
	if(args.size() == 3) {
		Val set = args[2]->eval(s,e);
		(*array)[i.to_i()] = set;
	}
	return (*array)[i.to_i()]; 
}

Val len(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 1) {
		cout << "len take exactly one argument" << endl;
		exit(1);
	}
	Val tab = rtov(args[0]->eval(s,e), s);
	
	if(tab.getType() != ARRAY) {
		cout << "len take as first argument an array" << endl;
		exit(1);
	}
	vector<Val>* array = tab.to_array();
	
	return Val((int) array->size()); 
}

Val list(Env* e, Store* s, vector<Expression*> args) {
	Val tab = array(e,s, vector<Expression*>());
	//fix me
	ValExpr* ex = new ValExpr(tab);
	args.insert(args.begin(), ex);
	return append(e,s, args);
}
