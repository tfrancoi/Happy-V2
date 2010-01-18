#include <string>
#include "parser.h"
#include "grammar.h"
#include <iostream>
using namespace std;

int analyse_node(LTerm *tree) {
	if(tree->getType() == 0) {
		cout << "on ne connait pas le type on va le trouver" << endl;
		//si le premier est terminal on applique la règle 1
		if((*tree)[0]->isTerminal()) {
			int type = (*tree)[0]->getType();
			tree->setType(getRule1()[type]);
			cout << tree->getType() << endl;
			//si c'est 0 erreur invalid token at child 1
		}
		else { //pas terminal alors on applique la règle 2
			
		}
		
	}
	return 0;
}

int analyse_tree(LTerm *tree) {
	string tab[] = {"Programme"};
	LTerm *prog = new LTerm();
	prog->add(tree);
	prog->setType(get_set_code("Programme"));
	prog->setGeneral(create_sets(tab, 1));
	prog->print(0);
	analyse_node(tree);
	return 0;
	
}
