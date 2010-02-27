#include "prog.h"
#include "../grammar.h"
#include <string>
#include <iostream>

using namespace std;

map<std::string, int>* vars_ref;
int j = 0;


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
	j = 0;
	vars_ref = &(this->vars);
	TTerm* t = dynamic_cast<TTerm*>( (*tree)[1]);
	this->name = t->getValue();
	LTerm* arg = dynamic_cast<LTerm*>( (*tree)[2]);
	analyse_arg(arg);
	LTerm* instr = dynamic_cast<LTerm*>( (*tree)[3]);
	::analyse_instr(instr, this->instr);
	this->nb_var = j;
}

string Function::getName() {
	return this->name;	
}

unsigned int Function::getNbVar() {
	return this->nb_var;
}

unsigned int Function::getArity() {
	return this->arity;
}

void Function::analyse_arg(LTerm* arg) {
	this->arity = arg->size() - 1;
	for(int i = 1; i < arg->size(); i++) {
		TTerm *t = dynamic_cast<TTerm*>((*arg)[i]);
		::add_var(t->getValue());
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
	return 0;
}

void add_var(string s) {
	if(get_var_ref(s) == 0) {
		set_var_ref(j, s);
		j++;
	}
}

int get_var_ref(string s) {
	return (*vars_ref)[s];
	
}

void set_var_ref(int j, string name) {
	(*vars_ref)[name] = j;
}




void analyse_block(LTerm* block, vector<Instr*>& v) {
	for(int i = 0; i < block->size(); i++) {
		LTerm* instr = dynamic_cast<LTerm*>( (*block)[i]);
		analyse_instr(instr, v);
	}
}
		
void analyse_instr(LTerm* instr, vector<Instr*>& v) {
	
	if(instr->getType() == get_set_code("Block_instr")) {
		analyse_block(instr, v);
	}
	if(instr->getType() == get_set_code("Call")) { 
		v.push_back(new Call(instr));
	}
	if(instr->getType() == get_set_code("Assignement")) { 
		Assignement* ass = new Assignement(instr);
		::add_var(ass->getVarName());
		ass->setVarRef(get_var_ref(ass->getVarName()));
		v.push_back(ass);
	}
	if(instr->getType() == get_set_code("Return")) {
		v.push_back(new Return(instr));
	}
	if(instr->getType() == get_set_code("If")) {
		If* cond = new If(instr);
		v.push_back(cond);
	}
	if(instr->getType() == get_set_code("While")) {
		While* boucle = new While(instr);
		v.push_back(boucle);
	}
	if(instr->getType() == get_set_code("Skip")) {
		Skip* boucle = new Skip(instr);
		v.push_back(boucle);
	}
	if(instr->getType() == get_set_code("Op")) {
		v.push_back(new Call(instr, 0));
	}
}

