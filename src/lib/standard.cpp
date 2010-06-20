#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../interpreter.h"
#include "standard.h"
#include "reference.h"

using namespace std;

void init_io(map<string, NFunction*> &native) {
	native["write"] = new NFunction(&write);
	native["get_i"] = new NFunction(&::get_int);
	native["get_r"] = new NFunction(&::get_real);
	native["get_s"] = new NFunction(&::get_string);
}
void init_arithmetic(map<string, NFunction*> &native) {		
	native["+"] = new NFunction(&::plus);
	native["-"] = new NFunction(&::moins);
	native["="] = new NFunction(&::egal);
	native["<"] = new NFunction(&::less);
	native["typeof"] = new NFunction(&::type);	
	native["rand"] = new NFunction(&::random);
}

Val write(Env* e, Store* s, vector<Expression*> args, int line, string file) {
	for(unsigned int i = 0; i < args.size(); i++) {
		Val v = rtov(args[i]->eval(s,e), s);		
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

Val plus(Env* e, Store* s, vector<Expression*> args, int line, string file) {
	if(args.size() < 2) {
		cout << "cannot use operator + for less then 2 arguments" << endl << "\t at line " << line << " in file " << file  << endl;
		exit(1);
	}
	Val v1 = rtov(args[0]->eval(s,e), s);
	Val v2 = rtov(args[1]->eval(s,e), s);
	Val result = simplePlus(v1,v2);
	for(unsigned int i = 2; i < args.size(); i++) {
		Val v = rtov(args[i]->eval(s,e), s);
		result = simplePlus(result, v);
	}
	
	return result;
}


Val moins(Env* e, Store* s, vector<Expression*> args, int line, string file) {
	if(args.size() != 2) {
		cout << "cannot use operator - for less or more then 2 arguments" << endl;
		exit(1);
	}
	Val v1 = rtov(args[0]->eval(s,e), s);
	Val v2 = rtov(args[1]->eval(s,e), s);
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

Val egal(Env* e, Store* s, vector<Expression*> args, int line, string file) {
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


Val less(Env* e, Store* s, vector<Expression*> args, int line, string file) {
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

Val type(Env* e, Store* s, vector<Expression*> args, int line, string file) {
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
	if(type1 ==REFERENCE) {
			return Val("ref");
	}
	if(type1 ==ARRAY) {
			return Val("list");
	}

	return Val("empty");
}

Val get_int(Env* e, Store* s, vector<Expression*> args, int line, string file) {
	if(args.size() > 0) {
		cout << "input function doesn't take any argument" << endl;
		exit(1);
	}
  int a = 0;
  cin >> a;
  return Val(a);
}

Val get_real(Env* e, Store* s, vector<Expression*> args, int line, string file) {
	if(args.size() > 0) {
		cout << "input function doesn't take any argument" << endl;
		exit(1);
	}
  double a = 0;
  cin >> a;
  return Val(a);
}

Val get_string(Env* e, Store* s, vector<Expression*> args, int line, string file) {
	if(args.size() > 0) {
		cout << "input function doesn't take any argument" << endl;
		exit(1);
	}
	
  string a = "";
  cin >> a;
  return Val(a);
}


Val random(Env* e, Store* s, vector<Expression*> args, int line, string file) {
	if(args.size() != 1) {
		cout << "rand take only one arg" << endl;
		exit(1);
	}
	srand(time(NULL));
	Val v1 = args[0]->eval(s,e);
	if(v1.getType() ==INTEGER) {
			return Val(rand() % (v1.to_i() + 1));
	}
	if(v1.getType() ==REAL) {
			double r = rand();
			return r / RAND_MAX * v1.to_f();
	}
	return Val();
}





