#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include <map>
#include "rep/prog.h"


class NFunction  {
	public :
		NFunction(Val (*f)(Env*, Store*, std::vector<Expression*>));
		int execute(Env*, Store*, std::vector<Expression*>);
	
	private :
		Val (*f)(Env*, Store*, std::vector<Expression*>);
};

void initNative();
int execute(Prog*, std::string[]);

Function* getProgFunction(std::string);

NFunction* getNativeFunction(std::string);


#endif
