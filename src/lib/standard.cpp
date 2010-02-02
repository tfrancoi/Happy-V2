#include <iostream>
#include "../interpreter.h"
#include "standard.h"

using namespace std;

Val write(Env* e, Store* s, vector<Expression*> args) {
	for(int i = 0; i < args.size(); i++) {
		Val v = args[i]->eval(s,e);
		cout << v.to_s();
		cout << " ";
	}
	cout << endl;
	
	
	return Val(1);
}
