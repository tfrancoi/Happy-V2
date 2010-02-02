#ifndef PROG_H
#define PROG_H

#include <string>
#include <map>
#include <vector>
#include "sem.h"
#include "expr.h"
#include "instr.h"
#include "../Term.h"

	


class Function {
	public :
		Function(LTerm*);
		std::string getName();
		int execute(Env*, Store*);
		int getNbVar();
		int getArity();
	private :		
		void analyse_arg(LTerm*);
		int analyse_block(LTerm*, int);
		int analyse_instr(LTerm*, int);
		std::vector<Instr*> instr;
		std::string name;
		std::map<std::string, int> vars;
		int arity;
		int nb_var;
		
};

class Prog {
	public:
		Prog(LTerm* );
		Function* getFunction(std::string );
		
	private:
		void analyse_block(LTerm*);
		void analyse_fun(LTerm*);
		std::map<std::string, Function*> functions;
	
	
};

int get_var_ref(std::string);

#endif
