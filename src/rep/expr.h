#ifndef EXPR_H
#define EXPR_H
#include <string>
#include "sem.h"


class SNode {
	public :
		SNode(Term* t);
		int line();
		std::string file();
	private : 
		int l;
		std::string f;
};

class Expression : public SNode {
	public :
		Expression(Term* t);
		/**
		 * @param s : le tas, l'endroit ou les objets sont alloués dynamiquement
		 *        e : environement ou pile, l'endroit ou les variables qui sont dans le scope
		 * 				se voient attribuer une valeur
		 * @return un objet val qui représente la valeur renvoyée
		 */ 
		virtual Val eval(Store* s, Env* e);
};


class Id : public Expression {
	public:
		Id(std::string s, int var_ref, Term* t);
		virtual Val eval(Store* s, Env* e);
		
	private :
		std::string name;
		int ref;
	
};

class Integer : public Expression {
	public:
		Integer(std::string s, Term* t);
		virtual Val eval(Store* s, Env* e);
	private :
		Val val;
	
};


class String : public Expression {
	public:
		String(std::string s, Term* t);
		virtual Val eval(Store* s, Env* e);
	private :
		Val val;
	
};


class Real : public Expression {
	public:
		Real(std::string s, Term* t);
		virtual Val eval(Store* s, Env* e);
	private :
		Val val;
	
};


class ValExpr : public Expression {
	public:
		ValExpr(Val v);
		virtual Val eval(Store* s, Env*e);
	private :
		Val val;
	
};



#endif
