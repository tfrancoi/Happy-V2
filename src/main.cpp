#include <iostream>
#include <cstring>

#include "preprocess.h"
#include "lexical.h"
#include "preprocess.h"
#include "grammar.h"
#include "parser.h"
#include "rep/prog.h"
#include "interpreter.h"

using namespace std;
string workDir;

string getFolder (const string& str) {
  size_t found;
  found=str.find_last_of("/\\");
  return str.substr(0,found+1);
}

string getWorkDir() {
	return workDir;
}

int analyse_arg(int argc, char** argv, char* file) {
	if(argc == 2) {
		strcpy(file, argv[1]);
		return 0;
	}
	return 9;
}

int main(int argc, char** argv) {
	char* file = new char[100];
	int result = analyse_arg(argc, argv, file);
  workDir = getFolder(file);
  init(); //init de la grammaire
	int error = 0; //erreur renvoyer par chaque sous process
	string out = file;
	LTerm *tree = new LTerm();
	Prog *main;
	switch(result) {
		case 0 : out = out + "p";
						 error = preprocess((const char*) file, out.c_str());
						 if(error) { return error; }
		case 1 : lexical_analyser((const char*) argv[1], out.c_str(), tree);
						 if(error) { return error; }
		case 2 : tree = prog_tree(tree);
						 error = analyse_tree(tree);
						 if(error) { return error; }
		case 3 : main = new Prog(tree);
	}
	
	return execute(main, NULL);
	
	
}
