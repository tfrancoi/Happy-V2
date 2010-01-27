#include "prog.h"
#include "../grammar.h"
#include <string>
#include <iostream>

using namespace std;

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

void Prog::analyse_fun(LTerm *tree) {
	TTerm* t = dynamic_cast<TTerm*>( (*tree)[1]);
	string name = t->getValue();
	cout << "nom " << name << endl; 
	
	
}

Prog::Prog(LTerm *tree) {
	analyse_block(tree);
}

Function::Function(LTerm *tree) {
	
}


