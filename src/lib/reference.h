#ifndef REFERENCE_H
#define REFERENCE_H

#include <vector>
#include "../interpreter.h"

Val rtov(Val v, Store* s);
void init_reference(std::map<std::string, NFunction*> &native);

//reference function
Val into_store(Env* e, Store* s, std::vector<Expression*> args);
Val get_into_store(Env* e, Store* s, std::vector<Expression*> args);
Val change_into_store(Env* e, Store* s, std::vector<Expression*> args);

//fonction on array
Val array(Env* e, Store* s, std::vector<Expression*> args);
Val append(Env* e, Store* s, std::vector<Expression*> args);
Val get_index(Env* e, Store* s, std::vector<Expression*> args);
Val len(Env* e, Store* s, std::vector<Expression*> args);
Val list(Env* e, Store* s, std::vector<Expression*> args);
#endif
