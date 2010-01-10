#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <map>
#include <string>



void init();


int get_set_code(std::string t);



class Pair {
	public :
		sets set;
		int nb; //0 pour n et -1 pour N
}

#endif
