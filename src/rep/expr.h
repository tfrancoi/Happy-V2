#ifndef EXPR_H
#define EXPR_H
#include <string>
#include "sem.h"

class Expression {
	public :
		/**
		 * @param s : le tas, l'endroit ou les objets sont alloués dynamiquement
		 *        e : environement ou pile, l'endroit ou les variables qui sont dans le scope
		 * 				se voient attribuer une valeur
		 * @return un objet val qui représente la valeur renvoyée
		 */ 
		virtual Val eval(Store* s, Env* e) = 0;
};


class Id : public Expression {
	public:
		Id(std::string s, int var_ref);
		virtual Val eval(Store* s, Env* e);
		
	private :
		std::string name;
		int ref;
	
};

class Integer : public Expression {
	public:
		Integer(std::string s);
		virtual Val eval(Store* s, Env* e);
	private :
		Val val;
	
};


class String : public Expression {
	public:
		String(std::string s);
		virtual Val eval(Store* s, Env* e);
	private :
		Val val;
	
};


class Real : public Expression {
	public:
		Real(std::string s);
		virtual Val eval(Store* s, Env* e);
	private :
		Val val;
	
};




#endif
