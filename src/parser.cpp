#include <string>
#include "parser.h"
#include "grammar.h"
#include <iostream>
#include <vector>
using namespace std;

sets rewriteCheck(Term* t) {
	sets s = getRule3()[t->getType()];
	s.insert(t->getType());
	return s * t->getGeneral();
}

int analyse_node(LTerm *tree) {
	if(tree->getType() == 0) {
		//si le premier est terminal on applique la règle 1
		if((*tree)[0]->isTerminal()) {
			int type = (*tree)[0]->getType();
			tree->setType(getRule1()[type]);
			if(tree->getType() == get_set_code("ERROR")) {
				cout << type << " ,?? " << endl;
				cout << "Invalid start list token at line " << tree->getLine() << " in file " << tree->getFile() << endl;
				return 3;
			}
		}
		else { //pas terminal alors on applique la règle 2
			int type = applyRule1_2(tree->getGeneral());
			if(type) {
				tree->setType(type);
			}
		}		
	}
	//règle pour déterminer le type spécifique de tree et pour vérifier que
	//ca colle bien
	
	sets r = rewriteCheck(tree);
	if(r.cardinality() == 0) {
		cout << "Error unexpected element during rewrite at line " << tree->getLine() << " in file " << tree->getFile() << endl;
		return 2;
	}
	if(r.cardinality() > 1)  {
		cout << "Ambiguité gros soucis ici at line " << tree->getLine() << " in file " << tree->getFile() << endl;
		return 99;
	}
	tree->setGeneral(r);
	
	//on connait maintenant le type spécifique du parent
	vector<Paire> r2 = getRule2()[tree->getType()];
	int child = 0;
	for(unsigned int i = 0; i < r2.size(); i++) {
		int nb = r2[i].nb;
		if(nb == -1) {
			nb = tree->size() - child;
			if(nb <= 0) {
				nb = 1;
			}
		}
		
		if(nb == 0)  {
			nb = tree->size() - child;
		}
		
		if((nb + child) > tree->size()) {
			cout << "Arity error at line " << tree->getLine() << " in file " << tree->getFile() << endl;
			return 1;
		}
		
		for(int j = 0; j < nb; j++) {
			(*tree)[child]->setGeneral(r2[i].s);
			child++;
		}
		
	}
	
	if(child < tree->size()) {
		cout << "Arity error at line " << tree->getLine() << " in file " << tree->getFile() << endl;
		return 1;
	}
	//on connait le type général du fils, on vérifie que ca colle bien avec le type spécifique
	//tree->print(0);
	//cout << "Analyse de type générale" << endl;
	for(int i =0; i < tree->size(); i++) {
		//on connait le type générale
		if((*tree)[i]->getType() != 0) {
			TTerm* t = dynamic_cast<TTerm*>((*tree)[i]);
			sets result = rewriteCheck(t);
			if(result.cardinality() == 0) {
				cout << "Error unexpected element while rewrite at line " << t->getLine() << " in file " << t->getFile() << endl;
				return 2;
			}
			if(result.cardinality() > 1)  {
				cout << "Ambiguité gros soucis ici ";
				return 99;
			}
			t->setGeneral(result);
			
		}
	}
	for(int i =0; i < tree->size(); i++) {
		if(!(*tree)[i]->isTerminal()) {
			LTerm* c = dynamic_cast<LTerm*>((*tree)[i]);
			int error  = analyse_node(c);
			if(error) 
				return error;
		}
	}
	//tree->print(0);
	
	return 0;
}

LTerm* prog_tree(LTerm* tree) {
	string tab[] = {"Programme"};
	LTerm *prog = new LTerm();
	prog->add(tree);
	prog->setType(get_set_code("Programme"));
	prog->setGeneral(create_sets(tab, 1));
	return prog;
}


int analyse_tree(LTerm *tree) {
	
	int error = analyse_node(tree);
	if(error) {
		return error;
	}
	//tree->print(0);
	
	return 0;
	
}
