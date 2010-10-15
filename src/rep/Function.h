#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include "../Term.h"

#define NATIVE_FUNCTION 1
#define USER_FUNCTION 2

class Env;
class Store;
class Instr;

class GenericFunction {
	public :
		virtual int getType() = 0;
};

namespace function {

	class Function : public GenericFunction {
		public :
			Function(LTerm*);
			std::string getName();
			int execute(Env*, Store*);
			unsigned int getNbVar();
			unsigned int getArity();
			std::string getVarName(int index);
			virtual int getType();
		private :		
			void analyse_arg(LTerm*);
			std::vector<Instr*> instr;
			std::string name;
			std::map<std::string, int> vars;
			std::map<int, std::string> vars_names;
			unsigned int arity;
			unsigned int nb_var;
		
	};
}

#endif
