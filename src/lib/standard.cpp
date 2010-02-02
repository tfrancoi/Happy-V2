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

Val plus(Env* e, Store* s, vector<Expression*> args) {
	vector<Val*> vals;
	int type = -1;
	Val result;
	for(unsigned int i = 0; i < args.size(); i++) {
		Val v = args[i]->eval(s,e);
		if(type == -1) {
			type = v.getType();
			
		}
		else {
			if(type != v.getType()) {
				cout << "cannot use operator + for different type" << endl;
				exit(1);
			}
			
		}
		if(type == getType("integer")) {
			v.value 
		}
		cout << v.to_s();
		cout << " ";
	}
	
	return Val(1);
}
