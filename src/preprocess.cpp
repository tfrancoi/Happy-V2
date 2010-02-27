/*
 * preprocess.cpp
 *
 *  Created on: 27-mai-2009
 *      Author: mythrys
 *
 * TODO : fix include for file in other directory or in standart library
 * [# include dir.dir2.file   #]
 * [# include std#dirlib.lib  #]
 */

#include <fstream>
#include <iostream>

#include <vector>
#include <string>
#include "lexical.h"
#include "preprocess.h"
#include "const_preprocess.h"


using namespace std;

vector<std::string> inc;

int isPreprocessorDir(string s) {
	if(s == OPEN_DIR_PREPOCESS )
		return 1;

	if(s == CLOSE_DIR_PREPROCESS)
		return -1;
		
	return 0;
}

int include(ofstream* os, const char* in, int line, const char* file) {
	for(unsigned int i = 0; i < inc.size(); i++) {
		if(inc[i] == in) {
			cout << "warning double include at line " << line << " in file " << file << endl;
			return 0;
		}
	}
	string inw = getWorkDir() + in;
	ifstream is;
	is.open(inw.c_str());

	if(is.fail()) {
		cout << "include error : cannot find " << inw << endl;
		return -1;
	}
	inc.push_back(in);
	is.close();
	*(os) << "[# begin " << in << " #]" << endl;
	int result = analyseFile(inw.c_str(), os);
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
	
	ifstream is;
	is.open (in);
	while ((c = is.get()) != -1)  {
		if(comment_level < 0) {
			cout << END_COMMENT_ERROR << " at line " << line << " in file : " << in << endl;
			return -1;
		}
		if(dir_level < 0 || dir_level > 1) {
			cout << "Erreur : Directive close before open or try to put a directive in a directive" 
					 << " at line " << line << " in file : " << in << endl;
			return -1;
		}
		if(isSpace(c) || isBrackets(c) != -1) {
			if(c == '\n') { line++; }
			
			if(!comment_level && !dir_level && !isComments(temp) && !isPreprocessorDir(temp) ) {
				*(os) << temp;				
			}
			if(isBrackets(c) == -1 || !comment_level) 
				*(os) << c;
			
			comment_level += isComments(temp);
			old_level = dir_level;
			dir_level += isPreprocessorDir(temp);
			if(dir_level && old_level) {
				directive.push_back(temp);
			}
			else if(!dir_level && old_level) {
				//appel de traitement de la directive
				if(directive_analyser(directive, os, line, in)) {
					return -1;
				}
				
				directive = vector<string>();
			}
			temp = "";
		}
		else {
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

/**
 * preprocess the file in and put the result in the file with the name out
 * @return 0 if everything went well
 * 				 1 otherwise
 */
int preprocess(const char* in, const char* out) {
	inc.push_back(in);
	ofstream os;
	os.open(out);

	int result = analyseFile(in, &os);
	if(result != 0) {
		return 1;
	}
	return 0;

}

/**
 * @return 
 *  1 if s open an happy comment
 * -1 if s close an happy comment
 *  0 else 
 */
int isComments(string s) {
	if(s == OPEN_COMMENT )
		return 1;
	if(s == CLOSE_COMMENT)
		return -1;

	return 0;
}
