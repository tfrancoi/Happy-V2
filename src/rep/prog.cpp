#include "prog.h"
#include "../grammar.h"
#include <string>
#include <iostream>

using namespace std;

map<std::string, int>* vars_ref;


Prog::Prog(LTerm *tree) {
	this->analyse_block(tree);
}

Function* Prog::getFunction(string name) {
	return functions[name];
}

void Prog::analyse_fun(LTerm *tree) {
	Function *f = new Function(tree);
	functions[f->getName()] = f;	
}

void Prog::analyse_block(LTerm *tree) {
	for(int i = 0; i < tree->size(); i++) {
		LTerm* fun = dynamic_cast<LTerm*>((*tree)[i]);
		if(fun->getType() == get_set_code("Block_fun")) {
			this->analyse_block(fun);
		}
		if(fun->getType() == get_set_code("Fun")) {			
			this->analyse_fun(fun);			
		}
	}
}

Function::Function(LTerm *tree) {
	vars_ref = &(this->vars);
	TTerm* t = dynamic_cast<TTerm*>( (*tree)[1]);
	this->name = t->getValue();
	LTerm* arg = dynamic_cast<LTerm*>( (*tree)[2]);
	analyse_arg(arg);
	LTerm* instr = dynamic_cast<LTerm*>( (*tree)[3]);
	int j = ::analyse_instr(instr, this->arity, this->instr);
	this->nb_var = j;
}

string Function::getName() {
	return this->name;	
}

int Function::getNbVar() {
	return this->nb_var;
}

int Function::getArity() {
	return this->arity;
}

void Function::analyse_arg(LTerm* arg) {
		this->arity = arg->size() - 1;
		int j = 0;
		for(int i = 1; i < arg->size(); i++) {
			TTerm *t = dynamic_cast<TTerm*>((*arg)[i]);
			vars[t->getValue()] = j;
			j++;
		}		
}

		



int Function::execute(Env* e, Store* s) {		
	for(unsigned int i = 0; i < instr.size(); i++) {
		int result = instr[i]->execute(e,s);
		if(result == 99) {
			return 0;
		}
		else if(result) {
			return result;
		}
	}		
}


int get_var_ref(string s) {
	return (*vars_ref)[s];
	
}

void set_var_ref(int j, string name) {
	(*vars_ref)[name] = j;
}


int analyse_block(LTerm* block, int number, vector<Instr*>& v) {
	int j = number;
	for(int i = 0; i < block->size(); i++) {
		LTerm* instr = dynamic_cast<LTerm*>( (*block)[i]);
		j = analyse_instr(instr, j, v);
	}
	
	return j;
}
		
int analyse_instr(LTerm* instr, int number, vector<Instr*>& v) {
	int j = number;
	if(instr->getType() == get_set_code("Block_instr")) {
		j = analyse_block(instr, j,v);
	}
	if(instr->getType() == get_set_code("Call")) { 
		v.push_back(new Call(instr, j));
	}
	if(instr->getType() == get_set_code("Assignement")) { 
		Assignement* ass = new Assignement(instr, j);
		
		if(get_var_ref(ass->getVarName()) == 0) {
			set_var_ref(j, ass->getVarName());
			j++;
		}
		ass->setVarRef(get_var_ref(ass->getVarName()));
		v.push_back(ass);
	}
	if(instr->getType() == get_set_code("Return")) {
		v.push_back(new Return(instr, j));
	}
	if(instr->getType() == get_set_code("If")) {
		If* cond = new If(instr, j);
		j = cond->getJ();
		v.push_back(cond);
	}
	if(instr->getType() == get_set_code("While")) {
		While* boucle = new While(instr, j);
		j = boucle->getJ();
		v.push_back(boucle);
	}
	return j;
}

