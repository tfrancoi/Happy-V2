#include <string>
#include <sstream>
#include <iostream>
#include "expr.h"

using namespace std;

SNode::SNode(Term* t) {
	if(t == NULL) {
		this->f = "unknown";
		this->l = 0;
	}
	else {
		this->f = t->getFile();
		this->l = t->getLine();
	}
}

int SNode::line() {
	return l;
}
string SNode::file() {
	return f;
}

Expression::Expression(Term* t) : SNode(t) {}
Val Expression::eval(Store* s, Env* e) {return Val();}

Integer::Integer(string s, Term* t) : Expression(t)  {
	int number;
	istringstream ss( s );
	ss >> number;
	val = Val(number);
}


Val Integer::eval(Store* s, Env* e) {
	return val;
}


String::String(string s, Term* t) : Expression(t) {
	val = Val(s);
}


Val String::eval(Store* s, Env* e) {
	return val;
}


Id::Id(string s, int var_ref, Term* t) : Expression(t) {
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

Real::Real(std::string s, Term* t) : Expression(t) {
	double number;
	istringstream ss( s );
	ss >> number;
	val = Val(number);
}
Val Real::eval(Store* s, Env* e) {
	return val;
}

ValExpr::ValExpr(Val v) : Expression(NULL) {
	val = v;
}
Val ValExpr::eval(Store* s, Env* e) {
	return val;
}

