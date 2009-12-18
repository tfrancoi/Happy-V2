#include "Term.h"
using namespace std;

Term::Term() {
	this->value = "";
	this->type = "empty";
}
	

Term::Term(string value, string type) {
	this->value = value;
	this->type = type;
}
			
Term::~Term() {}

string Term::getType() {
	return this->type;
}
			
string Term::getValue() {
	return this->value;
}
			

