#include <iostream>


#include "lexical.h"
#include "preprocess.h"
#include "grammar.h"
using namespace std;

int main(int argc, char** argv) {
	//init de la grammaire
	init();
	int error = 0; //erreur renvoyer par chaque sous process
	cout << "preprocess " << endl;
	error = preprocess((const char*) argv[1], (const char*) argv[2]);
	if(error) { return error; }
	lexical_analyser((const char*) argv[1], (const char*) argv[2]);
	if(error) { return error; }
}
