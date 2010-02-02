#ifndef EXPR_H
#define EXPR_H
#include <string>
#include "sem.h"

class Expression {
	public :
		Expression();
		virtual ~Expression();
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

class Integer : public Expression {
	public:
		Integer(std::string s);
		virtual Val eval(Store* s, Env* e);
	private :
		int val;
	
};


class String : public Expression {
	public:
		String(std::string s);
		virtual Val eval(Store* s, Env* e);
	private :
		std::string val;
	
};





#endif
