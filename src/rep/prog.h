#ifndef PROG_H
#define PROG_H

#include <string>
#include <map>
#include <vector>
#include "sem.h"
#include "expr.h"
#include "instr.h"
#include "../Term.h"
#include "Function.h"




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
void set_var_ref(int j, std::string name);
void add_var(std::string s);

void analyse_block(LTerm*, std::vector<Instr*>&);
void analyse_instr(LTerm*, std::vector<Instr*>&);
		

#endif
