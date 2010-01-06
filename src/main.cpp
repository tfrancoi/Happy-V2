#include <iostream>


#include "lexical.h"
#include "preprocess.h"

using namespace std;

int main(int argc, char** argv) {
	int error = 0; //erreur renvoyer par chaque sous process
	cout << "preprocess " << endl;
	error = preprocess((const char*) argv[1], (const char*) argv[2]);
	if(error) { return error; }
	lexical_analyser((const char*) argv[1], (const char*) argv[2]);
	if(error) { return error; }
}
