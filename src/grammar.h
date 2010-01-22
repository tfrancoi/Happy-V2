#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <map>
#include <string>
#include "set/sets.h"


void init();


int get_set_code(std::string t);
sets create_sets(std::string tab[], int size); 





class Paire {
	public :
		Paire(int nb, sets s);
		sets s;
		int nb; //0 pour n et -1 pour N
};

std::map<int, int> getRule1(); 
std::map<int, int> getRule1_2();
std::map<int, std::vector<Paire> > getRule2();
std::map<int, sets> getRule3();
int applyRule1_2(sets s);

#endif
