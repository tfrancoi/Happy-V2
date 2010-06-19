#include <string>
#include <sstream>
#include <iostream>
#include "expr.h"

using namespace std;

Integer::Integer(string s) {
	int number;
	istringstream ss( s );
	ss >> number;
	val = Val(number);
}


Val Integer::eval(Store* s, Env* e) {
	return val;
}


String::String(string s) {
	val = Val(s);
}


Val String::eval(Store* s, Env* e) {
	return val;
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

Real::Real(std::string s) {
	double number;
	istringstream ss( s );
	ss >> number;
	val = Val(number);
}
Val Real::eval(Store* s, Env* e) {
	return val;
}

ValExpr::ValExpr(Val v) {
	val = v;
}
Val ValExpr::eval(Store* s, Env* e) {
	return val;
}

