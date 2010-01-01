#ifndef LEXICAL_H
#define LEXICAL_H

#include <string>
#include "Term.h"
bool isSpace(const char);
char isBrackets(const char c) ;
/**
 * return 0 if there is no error then type contain the good type of the term
 * 				1 if there is an error then type contain the error
 * 
 */
int analyseTerm(const std::string value, std::string* type);

/**
 * Simplifie the tree, each list with one element become an atom
 * (a) -> a 
 * ((a)) -> a
 * ((a b c)) -> (a b c)
 */
void reduce(LTerm *tree);

#endif
