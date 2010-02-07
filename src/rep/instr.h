#ifndef INSTR_H
#define INSTR_H

#include <string>
#include "sem.h"
#include "expr.h"



Expression* create_expression(Term* t, int&);

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
		Call(LTerm*, int&);
		virtual int execute(Env*, Store*);
		virtual Val eval(Store* s, Env* e);
		
	private :
		std::string name;
		std::vector<Expression*> argument;
};

class Assignement : public Instr, public Expression {
		public:
			Assignement(LTerm*, int&);
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
		Return(LTerm*, int&);
		virtual int execute(Env*, Store*);
	private :
		Expression* expr;	
};


class If : public Instr {
	public :
		If(LTerm*, int);
		int getJ();
		virtual int execute(Env*, Store*);

	private :
		int executeList(Env*, Store*, std::vector<Instr*>&);
				
		int j;
		Expression* expr;
		std::vector<Instr*> yes;
		std::vector<Instr*> no;
};




class While : public Instr {
	public :
		While(LTerm*, int);
		int getJ();
		virtual int execute(Env*, Store*);

	private :
		int executeList(Env*, Store*, std::vector<Instr*>&);
		
		int j;
		Expression* expr;
		std::vector<Instr*> yes;
};



#endif
