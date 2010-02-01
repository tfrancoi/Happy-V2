#ifndef INSTR_H
#define INSTR_H

#include <string>
#include "sem.h"
#include "expr.h"


Expression* create_expression(Term* t);

class Instr {
	public:
		Instr();
		virtual ~Instr();
		/**
		 * @return error code, 0 if nothing wrong happened.
		 */ 
		virtual int execute(Env*, Store*);
	
};

class Call : public Instr, public Expression {
	public:
		Call(LTerm*);
		virtual int execute(Env*, Store*);
		virtual Val eval(Store* s, Env* e);
		
	private :
		std::string name;
		std::vector<Expression*> argument;
	
};

class Assignement : public Instr {
		public:
			Assignement(LTerm*);
			virtual int execute(Env*, Store*);
			std::string getVarName();
		private:
			std::string name;
			//Expression expr;
};

#endif
