#ifndef PROG_H
#define PROG_H

#include <string>
#include <map>
#include "../Term.h"

class Function {
	
	
};

class Prog {
	public :
		Prog(LTerm *tree);
	private :
		std::map<std::string, Function*> fun_list;
};

class Val {
	
};

class Store {
	
};

class Env {
	
};

class Expression {
	public :
		/**
		 * @param s : le tas, l'endroit ou les objets sont alloués dynamiquement
		 *        e : environement ou pile, l'endroit ou les variables qui sont dans le scope
		 * 				se voient attribuer une valeur
		 * @return un objet val qui représente la valeur renvoyée
		 */ 
		virtual Val eval(Store* s, Env* e);
};




class id : public Expression {
	private :
		std::string name;
		int ref;
	
};
#endif
