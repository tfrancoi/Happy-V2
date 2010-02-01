#include <string>
#include <sstream>

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
Expression::Expression() {}
Expression::~Expression() {}
Val Expression::eval(Store* s, Env* e) { return Val(); }
