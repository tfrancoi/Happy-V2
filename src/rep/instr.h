#ifndef INSTR_H
#define INSTR_H

#include <string>
#include "sem.h"
#include "expr.h"



Expression* create_expression(Term* t);

class Instr {
	public:
		/**
		 * @return error code, 0 if nothing wrong happened.
		 */ 
		virtual int execute(Env*, Store*) = 0;
	
};

class Call : public Instr, public Expression {
	public:
		Call(LTerm*);
		Call(LTerm*, int op);
		virtual int execute(Env*, Store*);
		virtual Val eval(Store* s, Env* e);
		
	private :
		std::string name;
		std::vector<Expression*> argument;
};

class Assignement : public Instr, public Expression {
		public:
			Assignement(LTerm*);
			virtual int execute(Env*, Store*);
			virtual Val eval(Store* s, Env* e);
			std::string getVarName();
			void setVarRef(int);
		private:
			std::string name;
			Expression* expr;
			int var_ref;
};

class Return : public Instr {
	public :
		Return(LTerm*);
		virtual int execute(Env*, Store*);
	private :
		Expression* expr;	
};


class If : public Instr {
	public :
		If(LTerm*);
		virtual int execute(Env*, Store*);

	private :
		int executeList(Env*, Store*, std::vector<Instr*>&);
				
		
		Expression* expr;
		std::vector<Instr*> yes;
		std::vector<Instr*> no;
};




class While : public Instr {
	public :
		While(LTerm*);
		virtual int execute(Env*, Store*);

	private :
		int executeList(Env*, Store*, std::vector<Instr*>&);
		Expression* expr;
		std::vector<Instr*> yes;
};

class Skip : public Instr {
	public :
		Skip(LTerm *);
		virtual int execute(Env*, Store*);
};



#endif
