#include "Term.h"
#include <iostream>
#include <typeinfo>
#include "grammar.h"
#include "set/sets.h"

using namespace std;

void indent(int level) {
	for(int i = 0; i < level; i++) {
		cout << ".  ";
	}
}

int Term::getLine() {
	return 0;
}

string Term::getFile() {
	return "";
}
int Term::isTerminal() {
	return 0;
}
void Term::print(int level) {
		cout << "erreur" << endl;	
}


int Term::getType() {
	return this->type;
}

sets Term::getGeneral() {
	return this->general;
}


void Term::setType(int type) {
	this->type = type;
}

void Term::setGeneral(sets gene) {
	this->general = gene;
}


TTerm::TTerm() {
	this->value = "";
	this->type = 0;
	this->file = "unknown";
	this->line = 0;
	
}
TTerm::TTerm(string value, string type, string file, int line) {
	this->value = value;
	this->type = get_set_code(type);
	this->file = file;
	this->line = line;
}
void TTerm::print(int level) {
	  indent(level);
		cout << "general : " << getGeneral().to_s() << "; type : " << this->type << "; value : " << this->value << 
				" in file " << file << " at line " << line << endl ;
}
int TTerm::isTerminal() {
	return 1;
}

string TTerm::getValue() {
	return this->value;
}



LTerm::LTerm() {
	list = vector<Term*>();
	setType(0);
}
void LTerm::add(Term *t) {
	list.push_back(t);
}

void LTerm::del_last() {
	list.pop_back();
}

int LTerm::isTerminal() {
	return 0;
}
int LTerm::size() {
	return list.size();
	
}
void LTerm::print(int level) {
	indent(level);
	cout << "[ type = "  << getType() << ", general = " << getGeneral().to_s() << endl;	
	for(unsigned int i = 0; i < list.size(); i++) {
		list[i]->print(level+1);
	}
	indent(level);
	cout << "]" << endl;
}
Term* LTerm::operator[] (unsigned int i) {
	if(i >= list.size()) 
		return new TTerm("error", "out of bound", "unknow", 0);
	else 
		return list[i];
}
Term* LTerm::flatten() {
	if(list.size() > 1) {
		return this;
	}
	
	//si on a affaire un atom
	if(list[0]->isTerminal()) {
		return this;
	}
	
	LTerm *cur = dynamic_cast<LTerm*> (list[0]);
	return cur->flatten();
}
void LTerm::set(unsigned int i, Term* t) {
	list[i] = t;
}


string TTerm::getFile() {
	return file;
}

int TTerm::getLine() {
	return line;
}


int LTerm::getLine() {
	return list[0]->getLine();
}

string LTerm::getFile() {
	return list[0]->getFile();
}


