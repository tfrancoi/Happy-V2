#include "Term.h"
#include <iostream>
#include <typeinfo>
using namespace std;

void indent(int level) {
	for(int i = 0; i < level; i++) {
		cout << ".  ";
	}
}

int Term::isTerminal() {
	return 0;
}

void Term::print(int level) {
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

void TTerm::print(int level) {
	  indent(level);
		cout << "type : " << this->type << "; value : " << this->value << endl ;
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

void LTerm::print(int level) {
	indent(level);
	cout << "[" << endl;	
	for(int i = 0; i < list.size(); i++) {
		list[i]->print(level+1);
	}
	indent(level);
	cout << "]" << endl;
}


Term* LTerm::operator[] (unsigned int i) {
	if(i >= list.size()) 
		return new TTerm("error", "out of bound");
	else 
		return list[i];
}


Term* LTerm::flatten() {
	if(list.size() > 1) {
		return this;
	}
	
	//si on a affaire un atom
	if(typeid(TTerm) == typeid(*list[0])) {
		return list[0];
	}
	
	LTerm *cur = dynamic_cast<LTerm*> (list[0]);
	return cur->flatten();
	
}

void LTerm::set(unsigned int i, Term* t) {
	list[i] = t;
	
}

