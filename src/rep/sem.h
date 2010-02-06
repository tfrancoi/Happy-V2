#ifndef SEM_H
#define SEM_H

#include <string>
#include <map>
#include <vector>
#include "../Term.h"


#define EMPTY 0
#define INTEGER 1
#define STRING 2

int getType(std::string);
void initType();

class Value {
	public : 
		virtual std::string to_s() = 0;
		virtual int to_i() = 0;
		virtual int to_b() = 0;
		
};

class Val {
	public :
		Val(int type, Value* v);
		Val();
		Val(int val);
		Val(std::string);
		int getType();
		std::string to_s();
		int to_i();
		int to_b();
		
	
	private :
		int type;
		Value* val;
	
};

class Store {
	
};


/**
 * Les arguments sont placés dans les premières case du tableau, les variables
 * déclaré dans la fonction se trouve  au milieu et la valeur de retour se situe à la fin
 */ 
class Env {
	public:
		Env(int nb_var);
		~Env();
		Val get(int);
		int set(int, Val);
		int getSize();
	private:
		Val* tab;
		int size; 
		
};

class Empty : public Value {
	public :
		virtual std::string to_s();
		virtual int to_i();
		virtual int to_b();
};
class Int : public Value {
	public :
		virtual std::string to_s();
		virtual int to_i();
		virtual int to_b();
		int val;
};

class Str : public Value {
	public :
		virtual std::string to_s();
		virtual int to_i();
		virtual int to_b();
		std::string val;
};


#endif
