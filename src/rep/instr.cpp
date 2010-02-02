#include <iostream>
#include "instr.h"
#include "prog.h"
#include "../grammar.h"
#include "../interpreter.h"

using namespace std;



Call::Call(LTerm* tree) {
		TTerm* t = dynamic_cast<TTerm*>((*tree)[0]);
		name = t->getValue();
		//cout << name << endl;
		for(int i = 1; i < tree->size(); i++) {
			argument.push_back(create_expression((*tree)[i]));
		}
}

int Call::execute(Env* e, Store* s) {
	Function *f = ::getProgFunction(name);
	if(f == NULL) {
			NFunction *nf = ::getNativeFunction(name);
			if(nf == NULL) {
				cout << "on est foutu " << endl;
			}
			else {
				//on execute la NFunction
				nf->execute(e,s,argument);
			}
	} 
	return 0;
}

Val Call::eval(Store* s, Env* e) {
	return Val();
}

Assignement::Assignement(LTerm* list) {
	TTerm* id = dynamic_cast<TTerm*>( (*list)[1]);
	this->name = id->getValue();
	TTerm* expression = dynamic_cast<TTerm*>( (*list)[2]);
	this->expr = create_expression(expression);
	
	
}
int Assignement::execute(Env* e, Store* s) {
	Val v = this->expr->eval(s,e);
	if(e->set(var_ref, v)) {
		cout << "variable hors des bornes de l'env boulet de programmeur " << endl;
		return 1;
	}
	return 0;
}
string Assignement::getVarName() {
	return this->name;
}

void Assignement::setVarRef(int ref) {
	this->var_ref = ref;
}


Expression* create_expression(Term* t) {
	if(t->getType() == get_set_code("int")) {
		TTerm* tt = dynamic_cast<TTerm*>(t);
		return new Integer(tt->getValue());
	}
	if(t->getType() == get_set_code("string")) {
		TTerm* tt = dynamic_cast<TTerm*>(t);
		return new String(tt->getValue());
	}
	
	if(t->getType() == get_set_code("Id")) {
		TTerm* tt = dynamic_cast<TTerm*>(t);
		return new Id(tt->getValue(), get_var_ref(tt->getValue()));
	}
	return new Expression();
}







Instr::Instr() {}
Instr::~Instr() {}
int Instr::execute(Env* e, Store* s) {cout << "ainsi soit-im" << endl; return 0;}
