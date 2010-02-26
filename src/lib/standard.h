#ifndef STANDARD_H
#define STANDARD_H

#include <vector>
#include "../interpreter.h"


//output functions
Val write(Env* e, Store* s, std::vector<Expression*> args);

//arithmetic and logic functions
Val plus(Env* e, Store* s, std::vector<Expression*> args);
Val egal(Env* e, Store* s, std::vector<Expression*> args);
Val moins(Env* e, Store* s, std::vector<Expression*> args);
Val less(Env* e, Store* s, std::vector<Expression*> args);

Val random(Env* e, Store* s, std::vector<Expression*> args);


Val type(Env* e, Store* s, std::vector<Expression*> args);

//input functions
Val get_int(Env* e, Store* s, std::vector<Expression*> args);
Val get_real(Env* e, Store* s, std::vector<Expression*> args);
Val get_string(Env* e, Store* s, std::vector<Expression*> args);


//reference function
Val into_store(Env* e, Store* s, std::vector<Expression*> args);
Val get_into_store(Env* e, Store* s, std::vector<Expression*> args);
Val change_into_store(Env* e, Store* s, std::vector<Expression*> args);
#endif
