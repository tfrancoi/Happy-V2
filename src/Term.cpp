#include "Term.h"
using namespace std;

int Term::isTerminal() {
	return 0;
}

TTerm::TTerm() {
	this->value = "";
	this->type = "empty";
}
	

TTerm::TTerm(string value, string type) {
	this->value = value;
	this->type = type;
}
			
TTerm::~TTerm() {}

int TTerm::isTerminal() {
	return 1;
}

string TTerm::getType() {
	return this->type;
}
			
string TTerm::getValue() {
	return this->value;
}
			

