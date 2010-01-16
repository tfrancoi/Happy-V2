#include <string>
#include "parser.h"
#include "grammar.h"
using namespace std;

int analyse_tree(LTerm *tree) {
	string tab[] = {"Programme"};
	LTerm *prog = new LTerm();
	prog->add(tree);
	prog->setType(get_set_code("Programme"));
	prog->setGeneral(create_sets(tab, 1));
	
	prog->print(0);
	
	return 0;
	
}
