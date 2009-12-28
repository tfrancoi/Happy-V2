#include "Term.h"
#include <iostream>
using namespace std;

int Term::isTerminal() {
	return 0;
}

void Term::print() {
		cout << "erreur" << endl;	
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

void TTerm::print() {
		cout << "value : " << this->value << "; " << endl;
}

int TTerm::isTerminal() {
	return 1;
}

string TTerm::getType() {
	return this->type;
}
			
string TTerm::getValue() {
	return this->value;
}
			
		
LTerm::LTerm() {
	list = vector<Term*>();
}


LTerm::~LTerm() {}

void LTerm::add(Term *t) {
	list.push_back(t);
}

int LTerm::isTerminal() {
	return 0;
}

int LTerm::size() {
	return list.size();
	
}

void LTerm::print() {
	cout << "( " ;	
	for(int i = 0; i < list.size(); i++) {
		list[i]->print();
	}
	cout << " )";
}


Term* LTerm::operator[] (unsigned int i) {
	if(i >= list.size()) 
		return new TTerm("error", "out of bound");
	else 
		return list[i];
}

