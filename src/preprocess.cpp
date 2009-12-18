/*
 * preprocess.cpp
 *
 *  Created on: 27-mai-2009
 *      Author: mythrys
 *
 * TODO : fix include for file in other directory or in standart library
 * [# include dir.dir2.file   #]
 * [# include std#dirlib.lib  #]
 * TODO : fix when main is call in an other directory, 
 * this directory became the working directory
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "lexical.h"
#include "preprocess.h"
#include "const_preprocess.h"

using namespace std;
vector<string> includes;

int isPreprocessorDir(string s) {
	if(s == OPEN_DIR_PREPOCESS )
		return 1;
	if(s == CLOSE_DIR_PREPROCESS) {
		return -1;
	}
	

	return 0;
}

int include(ofstream* os, const char* in, int line, const char* file) {
	for(int i = 0; i < includes.size(); i++) {
		if(includes[i] == in) {
			cout << "warning double include at line " << line << " in file " << file << endl;
			return 0;
		}
	}
	ifstream is;
	is.open(in);

	if(is.fail()) {
		cout << "include error cannot find " << in << endl;
		return -1;
	}
	includes.push_back(in);
	is.close();
	*(os) << "[# begin " << in << " #]" << endl;
	int result = analyseFile(in, os);
	*(os) << "[# end " << in << " #]" << endl;


	return result;
}

int directive_analyser(vector<string> dir, ofstream* os, int line, const char* file) {


	if(dir[0] == "include") {
		if(dir.size() != 2) {
			cout << "Syntax error in directive " << "at line " << line << " at file " << file << " : wrong arity" << endl;
			return -1;
		}
		return include(os, dir[1].data(),line,  file);


	}
	return 0;
}

int analyseFile(const char* in, ofstream* os) {
	char c;
	string temp = "";
	vector<string> directive;
	int line = 0;
	int comment_level = 0;
	int old_level = 0;
	int dir_level = 0;
	bool preprocess = false;
	ifstream is;
	is.open (in);
	while ((c = is.get()) != -1)  {
		if(comment_level < 0) {
			cout << END_COMMENT_ERROR << " at line " << line << endl;
			return -1;
		}
		if(dir_level < 0 || dir_level > 1) {
			cout << "Erreur : Directive close before open or try to put a directive in a directive" << " at line " << line << endl;
			return -1;
		}
		if(isSpace(c) || isBrackets(c) != -1) {
			if(c == '\n') { line++; }
			//cout << "brackets or space" << " level : "  << comment_level << endl;
			if(!comment_level && !dir_level && !isComments(temp) && !isPreprocessorDir(temp) ) {
				*(os) << temp;

			}
			*(os) << c;
			comment_level += isComments(temp);
			old_level = dir_level;
			dir_level += isPreprocessorDir(temp);
			if(dir_level && old_level) {
				directive.push_back(temp);
			}
			else if(!dir_level && old_level) {
				if(directive_analyser(directive, os, line, in)) {
					return -1;
				}
				//appel de traitement de la directive

				directive = vector<string>();
			}
			temp = "";
		}
		else {
			//cout << (int) c << "  " << c << endl;
			temp = temp + c;
		}    // get character from file
	}
	is.close();           // close file

	if(comment_level != 0) {
		cout << BALANCE_COMMENT_ERROR << endl;
		return -1;
	}
	return 0;

}

int preprocess(const char* in, const char* out) {
	includes.push_back(in);
	ofstream os;
	os.open(out);

	int result = analyseFile(in, &os);
	if(result != 0) {
		return -1;
	}
	return 0;

}

int isComments(string s) {
	if(s == OPEN_COMMENT )
		return 1;
	if(s == CLOSE_COMMENT) {
		return -1;
	}

	return 0;
}
