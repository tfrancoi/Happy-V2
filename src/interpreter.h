#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include <map>
#include "rep/prog.h"

#define VERBOSE 0


class NFunction : public GenericFunction {
	public :
		NFunction(Val (*f)(Env*, Store*, std::vector<Expression*>, int line, std::string));
		Val eval(Store* s, Env* e, std::vector<Expression*> args, int line, std::string);
		virtual int getType();
	
	private :
		Val (*f)(Env*, Store*, std::vector<Expression*>, int line, std::string);
};

void initNative();

int execute(Prog*, std::string[]);

function::Function* getProgFunction(std::string);

NFunction* getNativeFunction(std::string);

void runtime_error(std::string msg, int line, std::string file);

#endif
