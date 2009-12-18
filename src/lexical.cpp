
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "lexical.h"
#include "Stack.h"
#include "Term.h"
#include "preprocess.h"


using namespace std;

int main(int argc, char** argv) {

	preprocess((const char*) argv[1], (const char*) argv[2]);

	int level = 0;
	char c;
	string temp = "";


	ifstream is;
	is.open (argv[2]);

	int dir = 0; //indique si on est dans une directive
	int line = 1; //on démarre à la première ligne
	string file = argv[1];
	Stack<int> lines = Stack<int>();
	Stack<string> files = Stack<string>(); //on est dans le fichier d'origine
	vector<string> directive;
	while ((c = is.get()) != -1)  {

		if(isSpace(c)) {
			//cout << temp << " | ";
			if(c== '\n') {
				//cout << c;
				cout << file << " at line " << line << ": ";
				line++;
			}
			int d = isPreprocessorDir(temp);
			if(d == -1) {
				if(directive[0] == "begin") {
					lines.push(&line);
					files.push(&file);
					file = directive[1];
					line = 0;
				}
				if(directive[0] == "end") {
					line = *(lines.pop());
					file = *(files.pop());
				}
				directive = vector<string>();
				dir = 0;
			}
			else if(d) {
				dir = 1;
			}
			else {
				if(dir) {
					directive.push_back(temp);
				}
				//fait les trucs utiles
			}
			temp = "";
		}
		else if(isBrackets(c) != -1) {
			cout << endl <<"brackets" << c << endl;
			if(c == '(') {
				cout << ++level << endl;
			}
			else {
				cout << --level << endl;
			}
			Term t("" + c, "" + c);
		}
		else {
			//cout << (int) c << "  " << c << endl;
			temp = temp + c;
		}    // get character from file

	}

  is.close();           // close file
  Term t("salut", "id");
  cout << t.getValue() << endl;
  int a = 7;
  Stack<Term>* st = new Stack<Term>();
  st->push(&t);
  cout << st->pop()->getValue() << endl;
  return 0;

}

bool isSpace(const char c) {
	if(c == ' ' || c == '\n' || c == '\t' || c == '\r') {
		return true;
	}
	return false;
}

char isBrackets(const char c) {
	if(c == ')' || c == '(') {
		return c;
	}
	return (char) -1;
}
