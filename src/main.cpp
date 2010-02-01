#include <iostream>

#include "preprocess.h"
#include "lexical.h"
#include "grammar.h"
#include "parser.h"
#include "rep/prog.h"
#include "interpreter.h"

using namespace std;

int main(int argc, char** argv) {
	//init de la grammaire
	init();
	LTerm *tree = new LTerm();
	int error = 0; //erreur renvoyer par chaque sous process
	cout << "preprocess " << endl;
	error = preprocess((const char*) argv[1], (const char*) argv[2]);
	if(error) { return error; }
	cout << "Lexical " << endl;
	lexical_analyser((const char*) argv[1], (const char*) argv[2], tree);
	if(error) { return error; }
	cout << "Parser " << endl;
	tree = prog_tree(tree);
	error = analyse_tree(tree);
	if(error) { return error; }
	cout << "translation " << endl;
	initType();
	Prog *main = new Prog(tree);
	cout << "execution " << endl;
	execute(main, NULL);
	
	
}
