#include <iostream>
#include <cstdlib>
#include "../interpreter.h"
#include "standard.h"

using namespace std;

Val write(Env* e, Store* s, vector<Expression*> args) {
	for(unsigned int i = 0; i < args.size(); i++) {
		Val v = args[i]->eval(s,e);
		cout << v.to_s();
		cout << " ";
	}
	cout << endl;
	
	
	return Val(1);
}

Val simplePlus(Val arg1, Val arg2) {
	int type1 = arg1.getType();
	int type2 = arg2.getType();
	if(type1 ==INTEGER && type2 == INTEGER) {
		int i = arg1.to_i() + arg2.to_i();
		return Val(i);
	}
	if((type1 == INTEGER && type2 == REAL) || (type2 == INTEGER && type1 == REAL) ||  (type1 == REAL && type2 == REAL)) {
		double i = arg1.to_f() + arg2.to_f();
		return Val(i);		
	}
	if(type1 == STRING || type2 == STRING) {
			string i = arg1.to_s() + arg2.to_s();
			return Val(i);
	}
	
	
	return Val(1);
	
}

Val plus(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() < 2) {
		cout << "cannot use operator + for less then 2 arguments" << endl;
		exit(1);
	}
	Val v1 = args[0]->eval(s,e);
	Val v2 = args[1]->eval(s,e);
	Val result = simplePlus(v1,v2);
	for(unsigned int i = 2; i < args.size(); i++) {
		Val v = args[i]->eval(s,e);
		result = simplePlus(result, v);
	}
	
	return result;
}


Val moins(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 2) {
		cout << "cannot use operator - for less or more then 2 arguments" << endl;
		exit(1);
	}
	Val v1 = args[0]->eval(s,e);
	Val v2 = args[1]->eval(s,e);
	int type1 = v1.getType();
	int type2 = v2.getType();
	if(type1 ==INTEGER && type2 == INTEGER) {
		int i = v1.to_i() - v2.to_i();
		return Val(i);
	}
	if((type1 == INTEGER && type2 == REAL) || (type2 == INTEGER && type1 == REAL) ||  (type1 == REAL && type2 == REAL)) {
		double i = v1.to_f() - v2.to_f();
		return Val(i);		
	}
	
	return Val(0);
}

Val egal(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 2) {
		cout << "cannot use operator = for less then 2 arguments" << endl;
		exit(1);
	}
	Val v1 = args[0]->eval(s,e);
	Val v2 = args[1]->eval(s,e);
	int type1 = v1.getType();
	int type2 = v2.getType();
	if(type1 == type2) {
		if(type1 ==INTEGER) {
			int i = v1.to_i() == v2.to_i();
			return Val(i);
		}
		if(type1 == STRING) {
			int i = v1.to_s() == v2.to_s();
			return Val(i);
		}
	}
	if((type1 == INTEGER && type2 == REAL) || (type2 == INTEGER && type1 == REAL) ||  (type1 == REAL && type2 == REAL)) {
		int i = v1.to_f() == v2.to_f();
		return Val(i);
	}
	return Val(0);	
}


Val less(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 2) {
		cout << "cannot use operator < for less or more then 2 arguments" << endl;
		exit(1);
	}
	Val v1 = args[0]->eval(s,e);
	Val v2 = args[1]->eval(s,e);
	int type1 = v1.getType();
	int type2 = v2.getType();
	if(type1 == type2) {
		if(type1 ==INTEGER) {
			int i = v1.to_i() < v2.to_i();
			return Val(i);
		}
	}
	if((type1 == INTEGER && type2 == REAL) || (type2 == INTEGER && type1 == REAL) ||  (type1 == REAL && type2 == REAL)) {
		int i = v1.to_f() < v2.to_f();
		return Val(i);
	}
	return Val(0);	
}

Val type(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() != 1) {
		cout << "cannot use operator typeof for more then 1 arguments" << endl;
		exit(1);
	}
	Val v1 = args[0]->eval(s,e);
	int type1 = v1.getType();
	if(type1 ==INTEGER) {
			return Val("int");
	}
	if(type1 ==STRING) {
			return Val("string");
	}
	if(type1 ==REAL) {
			return Val("real");
	}
	return Val("empty");
}

string input(Env* e, Store* s, vector<Expression*> args) {
	if(args.size() > 0) {
		cout << "input function doesn't take any argument" << endl;
		exit(1);
	}
	return "";
}

Val get_int(Env* e, Store* s, vector<Expression*> args) {
	return Val();
}
