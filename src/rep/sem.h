#ifndef SEM_H
#define SEM_H

#include <string>
#include <map>
#include <vector>
#include "../Term.h"
int getType(std::string);
void initType();

class Value {};

class Val {
	public :
		Val(int type, Value v);
		Val();
		Val(int val);
		int getType();
	
	private :
		int type;
		Value val;
	
};

class Store {
	
};


/**
 * Les arguments sont placés dans les premières case du tableau, les variables
 * déclaré dans la fonction se trouve  au milieu et la valeur de retour se situe à la fin
 */ 
class Env {
	public:
		Env(int nb_var);
		~Env();
		Val get(int);
		int set(int, Val);
	private:
		Val* tab;
		int size; 
		
};

class Empty : public Value {};
class Int : public Value {
		public :
			int val;
};


#endif
