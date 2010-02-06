#ifndef STANDARD_H
#define STANDARD_H

#include <vector>
#include "../interpreter.h"


Val write(Env* e, Store* s, std::vector<Expression*> args);
Val plus(Env* e, Store* s, std::vector<Expression*> args);
Val egal(Env* e, Store* s, std::vector<Expression*> args);
Val moins(Env* e, Store* s, std::vector<Expression*> args);
Val less(Env* e, Store* s, std::vector<Expression*> args);


#endif
