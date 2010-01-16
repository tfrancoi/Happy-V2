
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

#include "lexical.h"
#include "Stack.h"
#include "Term.h"
#include "preprocess.h"



using namespace std;

int lexical_analyser(const char* main_file, const char* preprocess_file, LTerm *cur) {
	

	int level = 0;
	char c;
	string temp = "";


	ifstream is;
	is.open (preprocess_file);

	int dir = 0; //indique si on est dans une directive
	int line = 1; //on démarre à la première ligne
	int str = 0;
	int echapement = 0; //caractère d'échapement dans les strings
	string file = main_file;
	vector<int> lines = vector<int>();
	vector<string> files = vector<string>(); //on est dans le fichier d'origine
	vector<string> directive;
	
	Stack<LTerm> term_stack = Stack<LTerm>();	
	
	
	cout << "lexical parser " << endl;
	while ((c = is.get()) != -1)  {

		if(c == '"' && !echapement) {
			str = 1 - str;
			if(!str) { //on vient de finir un string on crée le term
				cur->add(new TTerm(temp, "string", file, line));
				temp = "";
			}
		} 
		else if(str) {
			if(c == '\\' && !echapement)
				echapement = 1;
			else {
				temp = temp + c;
				echapement = 0;
			}
		}
		else if(isSpace(c) || isBrackets(c) != -1) {
			
			
			int d = isPreprocessorDir(temp);
			if(d == -1) {
				if(directive[0] == "begin") {
					lines.push_back(line);
					files.push_back(file);
					file = directive[1];
					line = 0;
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
					string *type = new string();
					analyseTerm(temp, type);
					//cout << "line == " << line << endl;
					int l = line;
					//if(c == '\n') { l--;}
					cur->add(new TTerm(temp, *type, file, l));
				}
			}
			temp = "";
			
			if(isBrackets(c) != -1) {
				if(c == '(') {
					LTerm *t = new LTerm();
					
					cur->add(t);
					term_stack.push(cur);
					cur = t;
						
					++level;
				}
				else {
					--level;
					if(level < 0) {
						cout << "Too much end brackets, cannot reach a level higher than root level at line " << line << " in file " << file << endl;
						return 2;
					}
					int size = cur->size(); 
					cur = term_stack.pop();
					if(size  < 1) {
						cout << "Warning : Empty list of atom in " << file << " at line " << line  << endl;
						cur->del_last();
					}
					
					
				}
				
				
			}
			
			if(c== '\n') { line++; }
		}
		

		else {
			temp = temp + c;
		}    // get character from file

	}
	
	if(level != 0) {
		cout << "Error too much brackets or not enough, programm tree corrupt" << endl;
		return 1;
	}
	
	
	reduce(cur);
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

char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
string reserved_word[] = {"fun", "if", "while", "set", "skip", "of"};
const int nb_reserved_word = 6;

bool contain(char c , char* tab, int size) {
	for(int i = 0; i < size; i++) {
		if(c == tab[i]) {
			return true;
		}
	}	
	return false;
}

bool contain(string c , string tab[], int size) {
	for(int i = 0; i < size; i++) {
		if(c == tab[i]) {
			return true;
		}
	}	
	return false;
}

int analyseTerm(const string value, string* type) {
	//check if it's a number
	if(contain(value[0], digit, 10) || value[0] == '-') {
		int floating = 0;
		int number = 1; 
		for(unsigned int i = 1; i < value.size(); i++) {
			if(value[i] == ',') { 
				floating++;
			}
			else {
				if(!contain(value[i], digit, 10)) {
					number=0;
				}
			}
				
			
		}
		if(number && floating == 1) {
			type->append("float");
			return 0;
		}
		if(number && floating == 0) {
			type->append("int");
			return 0;
		}
	}	
	if(contain(value, reserved_word, nb_reserved_word)) {
		type->append(value);
		return 0;
	}
	type->append("Id");
	return 0;
}

Term* simplify(Term *t) {
	if(t->isTerminal()) {
		return t;
	}
	
	LTerm *cur = dynamic_cast<LTerm*> (t);
	Term* c = cur->flatten();
	
	if(c->isTerminal()) {
		return c;
	}
	
	LTerm *cur1 = dynamic_cast<LTerm*> (c);
	reduce(cur1);
	return cur1;
}


void reduce(LTerm *tree) {
	for(int i = 0; i < tree->size(); i++) {
			tree->set(i, simplify((*tree)[i]));
	}
	Term *f = tree->flatten();
	if(!f->isTerminal()) {
		LTerm *t = dynamic_cast<LTerm*>(f);
		*tree = *t;
	}
}
