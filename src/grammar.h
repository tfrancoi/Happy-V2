#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <map>
#include <string>
#include "set/sets.h"


void init();


int get_set_code(std::string t);



class Paire {
	public :
		Paire(int nb, sets s);
		sets s;
		int nb; //0 pour n et -1 pour N
};

#endif