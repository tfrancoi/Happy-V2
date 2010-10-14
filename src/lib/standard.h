#ifndef STANDARD_H
#define STANDARD_H

#include <vector>
#include "../interpreter.h"



void init_io(std::map<std::string, NFunction*> &native);
void init_arithmetic(std::map<std::string, NFunction*> &native);
//output functions
Val write(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);

//arithmetic and logic functions
Val plus(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val egal(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val moins(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val less(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);

Val random(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);


Val type(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);

//input functions
Val get_int(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val get_real(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val get_string(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);


#endif
