#ifndef PROG_H
#define PROG_H

#include <string>
#include <map>
#include <vector>
#include "../Term.h"









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


class Instr {
	public:
		Instr(LTerm *);
		virtual ~Instr();
		/**
		 * @return error code, 0 if nothing wrong happened.
		 */ 
		virtual int execute(Env*, Store*);
	
};


class Function {
	public :
		Function(LTerm*);
	
	private :
		
		
		std::vector<Instr> instr;
		std::string name;
		int arity;
		
};

class Prog {
	public:
		Prog(LTerm* );
		int execute(std::string[] );
		Function* getFunction(std::string );
		
	private:
		void analyse_block(LTerm*);
		void analyse_fun(LTerm*);
		std::map<std::string, Function*> functions;
	
	
};
#endif
