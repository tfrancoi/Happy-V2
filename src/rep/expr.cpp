#include <string>
#include <sstream>
#include <iostream>
#include "expr.h"

using namespace std;

Integer::Integer(string s) {
	int number;
	istringstream ss( s );
	ss >> number;
	val = number;
}


Val Integer::eval(Store* s, Env* e) {
	return Val(val);
}


String::String(string s) {
	val = s;
}


Val String::eval(Store* s, Env* e) {
	return Val(val);
}


Id::Id(string s, int var_ref) {
	this->name = s;
	this->ref = var_ref;
}
Val Id::eval(Store* s, Env* e) {
	Val v = e->get(ref);
	if(v.to_s() == "(-)") {
		cout << "variable " << name  << " not define " << endl;
	}
	return v;
}

Expression::Expression() {}
Expression::~Expression() {}
Val Expression::eval(Store* s, Env* e) { return Val(); }
