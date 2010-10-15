#include <iostream>
#include <cstdlib>
#include "instr.h"
#include "prog.h"
#include "../grammar.h"
#include "../interpreter.h"

using namespace std;
using namespace rep;

Call::Call(LTerm* tree) : Expression(tree) {
		TTerm* t = dynamic_cast<TTerm*>((*tree)[0]);
		name = t->getValue();
		for(int i = 1; i < tree->size(); i++) {
			argument.push_back(create_expression((*tree)[i]));
		}
}

Call::Call(LTerm* tree, int op) : Expression(tree) {
		TTerm* t = dynamic_cast<TTerm*>((*tree)[2]);
		name = t->getValue();
		argument.push_back(create_expression((*tree)[1]));
		for(int i = 3; i < tree->size(); i++) {
			argument.push_back(create_expression((*tree)[i]));
		}
}

int Call::execute(Env* e, Store* s)  {
	this->eval(s,e);
	return 0;
}

Val Call::eval(Store* s, Env* e) {
	function::Function *f = NULL; 
	NFunction *nf = NULL; 
	Val v = e->get(this->name);
	if(VERBOSE)
		cout << "call => " << name << endl;
		
	if(v.getType() == FUNCTION) {
		if(v.to_function()->getType() == NATIVE_FUNCTION) {
			nf = dynamic_cast<NFunction*>(v.to_function());
		}
		else {
			f = dynamic_cast<function::Function*>(v.to_function());
		}
	}
	else {		
		f = ::getProgFunction(name);
		nf = ::getNativeFunction(name);
	}
	
	
	
	if(f != NULL) {
		Env *ne = new Env(f->getNbVar());
		if(argument.size() != f->getArity()) {
			cout << "wrong arity during calling " << name << ", expected " << f->getArity() << ", " <<  argument.size() << " given " << endl;
			exit(1);
		}
		for(unsigned int i = 0; i < argument.size(); i++) {			
			ne->set(i, argument[i]->eval(s,e), f->getVarName(i));			
		}
		f->execute(ne, s);
		Val v = ne->get(f->getNbVar()); 
		delete ne;
		return v;		
	}
	if(nf != NULL) {
		return nf->eval(s,e,argument, this->line(), this->file());
	}
	cout << "undefined symbol "  << name << endl;
	return Val();
}



Assignement::Assignement(LTerm* list) : Expression(list) {
	TTerm* id = dynamic_cast<TTerm*>( (*list)[1]);
	this->name = id->getValue();
	this->expr = create_expression((*list)[2]);	
}

int Assignement::execute(Env* e, Store* s) {
	Val v = eval(s,e);
	
	if(v.getType() == EMPTY) {
		return 1;
	}
	return 0;
}




Val Assignement::eval(Store* s, Env* e) {
	Val v = this->expr->eval(s,e);
	/*if(v.getType() == REFERENCE) {
		cout << "référence set"  << v.to_s() << endl;
	}*/
	if(e->set(var_ref, v, name)) {
		cout << "variable hors des bornes de l'env boulet de programmeur " << endl;
		return Val();
	}
	return v;
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
		return new Integer(tt->getValue(), tt);
	}
	if(t->getType() == get_set_code("float")) {
		TTerm* tt = dynamic_cast<TTerm*>(t);
		return new Real(tt->getValue(), tt);
	}
	if(t->getType() == get_set_code("string")) {
		TTerm* tt = dynamic_cast<TTerm*>(t);
		return new String(tt->getValue(), tt);
	}
	if(t->getType() == get_set_code("Id")) {
		TTerm* tt = dynamic_cast<TTerm*>(t);
		return new Id(tt->getValue(), get_var_ref(tt->getValue()), tt);
	}
	if(t->getType() == get_set_code("Call")) {
		LTerm* lt = dynamic_cast<LTerm*>(t);
		return new Call(lt);
	}
	if(t->getType() == get_set_code("Op")) {
		LTerm* lt = dynamic_cast<LTerm*>(t);
		return new Call(lt, 0);
	}
	if(t->getType() == get_set_code("Assignement")) {
		LTerm* lt = dynamic_cast<LTerm*>(t);
		Assignement* ass = new Assignement(lt);
		
		::add_var(ass->getVarName());
		ass->setVarRef(get_var_ref(ass->getVarName()));
		return ass;
	}
	return NULL;
}


Return::Return(LTerm* list) : SNode(list) {
	this->expr = create_expression((*list)[1]);	
}

int Return::execute(Env* e, Store* s) {
	//on place la valeur du return dans la dernière case de l'environement
	e->set(e->getSize() - 1, this->expr->eval(s,e));
	return 99;
}

If::If(LTerm *tree) : SNode(tree) {
	this->expr = create_expression((*tree)[1]);
	LTerm *t = dynamic_cast<LTerm*>((*tree)[2]);
	::analyse_instr(t, yes);
	LTerm *tt = dynamic_cast<LTerm*>((*tree)[3]);
	::analyse_instr(tt, no);
}

int If::execute(Env* e, Store* s) {
	if(expr->eval(s,e).to_b()) {
		executeList(e,s,yes);
	}
	else {
		executeList(e,s,no);
	}
	return 0;
}


int If::executeList(Env* e, Store* s, std::vector<Instr*>& instr) {
	for(unsigned int i = 0; i < instr.size(); i++) {
		int result = instr[i]->execute(e,s);
		if(result == 99) {
			return 99;
		}
		else if(result) {
			return result;
		}
	}	
	return 0;	
}


While::While(LTerm *tree) : SNode(tree) {
	this->expr = create_expression((*tree)[1]);
	LTerm *t = dynamic_cast<LTerm*>((*tree)[2]);
	::analyse_instr(t, yes);
}


int While::execute(Env* e, Store* s) { 
	while(expr->eval(s,e).to_b()) {
		int result = executeList(e,s,yes); 
		if(result == 99) {
			return 99;
		}
		else if(result) {
			return result;
		}
	}
	return 0;
}


int While::executeList(Env* e, Store* s, std::vector<Instr*>& instr) {
	for(unsigned int i = 0; i < instr.size(); i++) {
		int result = instr[i]->execute(e,s);
		if(result == 99) {
			return 99;
		}
		else if(result) {
			return result;
		}
	}	
	return 0;	
}


Skip::Skip(LTerm *tree) : SNode(tree) {}
int Skip::execute(Env*, Store*) {return 0;}


