#ifndef REFERENCE_H
#define REFERENCE_H

#include <vector>
#include "../interpreter.h"

Val rtov(Val v, Store* s);
void init_reference(std::map<std::string, NFunction*> &native);

//reference function
Val into_store(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val get_into_store(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val change_into_store(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);

//fonction on array
Val array(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val append(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val get_index(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
Val len(Env* e, Store* s, std::vector<Expression*> args, int line, std::string file);
#endif
