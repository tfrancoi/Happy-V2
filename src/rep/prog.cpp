#include "prog.h"
#include "../grammar.h"
#include <string>
#include <iostream>

using namespace std;



Prog::Prog(LTerm *tree) {
	analyse_block(tree);
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
			analyse_block(fun);
		}
		if(fun->getType() == get_set_code("Fun")) {			
			analyse_fun(fun);			
		}
	}
}

Function::Function(LTerm *tree) {
	TTerm* t = dynamic_cast<TTerm*>( (*tree)[1]);
	this->name = t->getValue();
	LTerm* arg = dynamic_cast<LTerm*>( (*tree)[2]);
	analyse_arg(arg);
	LTerm* instr = dynamic_cast<LTerm*>( (*tree)[3]);
	int j = analyse_instr(instr, this->arity);
	//cout << "total de var " << j << endl;
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

int Function::analyse_block(LTerm* block, int number) {
	int j = number;
	for(int i = 0; i < block->size(); i++) {
		LTerm* instr = dynamic_cast<LTerm*>( (*block)[i]);
		j = analyse_instr(instr, j);
	}
	
	return j;
}
		
int Function::analyse_instr(LTerm* instr, int number) {
	int j = number;
	if(instr->getType() == get_set_code("Block_instr")) {
		j = analyse_block(instr, j);
	}
	if(instr->getType() == get_set_code("Call")) { 
		this->instr.push_back(new Call(instr));
	}
	if(instr->getType() == get_set_code("Assignement")) { 
		Assignement* ass = new Assignement(instr);
		this->instr.push_back(ass);
		if(vars[ass->getVarName()] == 0) {
			vars[ass->getVarName()] = j;
			j++;
		}
		//cout << "set " << ass->getVarName() << endl;
	}
	return j;
}


int Function::execute(Env* e, Store* s) {		
		for(int i = 0; i < instr.size(); i++) {
			instr[i]->execute(e,s);
		}		
}



