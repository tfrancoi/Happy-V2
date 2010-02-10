#include <iostream>

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

int main(int argc, char** argv) {
	string str1 ("/usr/bin/man");
  string str2 ("c:\\windows\\winhelp.exe");

  workDir = getFolder(argv[1]);
  

  
	//init de la grammaire
	string out = argv[1];
	out = out + "p";
	
	init();
	LTerm *tree = new LTerm();
	int error = 0; //erreur renvoyer par chaque sous process
	cout << "preprocess " << endl;
	error = preprocess((const char*) argv[1], out.c_str());
	if(error) { return error; }
	cout << "Lexical " << endl;
	lexical_analyser((const char*) argv[1], out.c_str(), tree);
	if(error) { return error; }
	cout << "Parser " << endl;
	tree = prog_tree(tree);
	error = analyse_tree(tree);
	if(error) { return error; }
	cout << "translation " << endl;
	Prog *main = new Prog(tree);
	cout << "execution " << endl;
	cout << "--------------------------" << endl << endl;
	return execute(main, NULL);
	
	
}
