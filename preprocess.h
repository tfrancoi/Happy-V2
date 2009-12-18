
#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <string>
#include <fstream>


int preprocess(const char* , const char*);

/**
 * return -1 if end a comment block
 * return 1 if begin a comment block
 * return 0 in other case
 */
int isComments(std::string);

int isPreprocessorDir(std::string s);

int analyseFile(const char* in, std::ofstream* os);

#endif /* PREPROCESS_H_ */


