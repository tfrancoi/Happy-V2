#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include "../Term.h"

class Env;
class Store;
class Instr;


class Function {
	public :
		Function(LTerm*);
		std::string getName();
		int execute(Env*, Store*);
		unsigned int getNbVar();
		unsigned int getArity();
		std::string getVarName(int index);
	private :		
		void analyse_arg(LTerm*);
		std::vector<Instr*> instr;
		std::string name;
		std::map<std::string, int> vars;
		std::map<int, std::string> vars_names;
		unsigned int arity;
		unsigned int nb_var;
		
};

#endif
