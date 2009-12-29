
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
	int str = 0;
	string file = argv[1];
	vector<int> lines = vector<int>();
	vector<string> files = vector<string>(); //on est dans le fichier d'origine
	vector<string> directive;
	
	Stack<LTerm> term_stack = Stack<LTerm>();	
	LTerm *cur = new LTerm();
	while ((c = is.get()) != -1)  {

		if(c == '"') {
			str = 1 - str;
			if(!str) { //on vient de finir un string on crée le term
				cur->add(new TTerm(temp, "string"));
				temp = "";
			}
		} 
		else if(str) {
			temp = temp + c;
		}
		else if(isSpace(c) || isBrackets(c) != -1) {
			//cout << temp << " | ";
			if(c== '\n') {		
				//cout << c;
				line++;				
			}
			
			int d = isPreprocessorDir(temp);
			if(d == -1) {
				if(directive[0] == "begin") {
					lines.push_back(line);
					files.push_back(file);
					file = directive[1];
					line = 1;
				}
				if(directive[0] == "end") {
					line = lines.back();
					lines.pop_back();
					file = files.back();
					files.pop_back();
					line--;
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
				else if(temp != "") {
					cur->add(new TTerm(temp, "autre"));
					//cout << file << " - " << line << ": " << temp << " ";
				}
				//fait les trucs utiles
			}
			temp = "";
			
			if(isBrackets(c) != -1) {
				//cout << file << " - " << line << ": " << c << " ";
				if(c == '(') {
					LTerm *t = new LTerm();
					
					cur->add(t);
					term_stack.push(cur);
					cur = t;
					//cur->add(new TTerm(string(1, c), string(1, c)));
					//cur->print();
					
					++level;
				}
				else {
					//cur->add(new TTerm(string(1, c), string(1, c)));
					cur = term_stack.pop();
					--level;
				}
				
				
			}
		}
		

		else {
			//cout << (int) c << "  " << c << endl;
			temp = temp + c;
		}    // get character from file

	}
	cur->print(0);

  is.close();           // close file
  
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
