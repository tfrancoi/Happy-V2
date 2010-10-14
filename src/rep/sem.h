#ifndef SEM_H
#define SEM_H

#include <string>
#include <map>
#include <vector>
#include "../Term.h"
#include "Function.h"


#define EMPTY 0
#define INTEGER 1
#define REAL 2
#define STRING 3
#define REFERENCE 4
#define ARRAY 5
#define OBJECT 6
#define FUNCTION 7

class Function;

namespace obj {
	class Object;
}

namespace rep {
	class Value;
}

class Val {
		public :
			Val(unsigned int ref); //crée une référence
			Val(); //crée une valeur vide
			Val(int); //crée un int
			Val(std::string); //crée un string
			Val(double); //crée un double
			Val(std::vector<Val>*); //crée un array
			Val(Function*);
			Val(obj::Object*); //crée un objet
			int getType();
			std::string to_s();
			int to_i();
			int to_b();
			double to_f();
			unsigned int get_ref();	
			std::vector<Val>* to_array();
			obj::Object* to_object();
			::Function* to_function();	
		
		private :
			int type;
			rep::Value* val;
			unsigned int ref;
		
	};

	class Store {
		public:
			Store();
			Val getVal(unsigned int adress);
			unsigned int newVal(Val);
			void setVal(Val, unsigned int adress);
		private:
			std::vector<Val> store;
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
			Val get(std::string);
			int set(int, Val);
			int set(int, Val, std::string name);
			int getSize();
		private:
			Val* tab;
			int size; 
			std::map<std::string, int> names;
		
	};




	
namespace rep {
	class Value {
		public : 
			virtual std::string to_s() = 0;
			virtual int to_i() = 0;
			virtual int to_b() = 0;
			virtual double to_f() = 0;
			virtual std::vector<Val>* to_array() = 0;
			virtual obj::Object* to_object() = 0;
			virtual ::Function* to_function() = 0;			
	};

	class Empty : public Value {
		public :
			virtual std::string to_s();
			virtual int to_i();
			virtual int to_b();
			virtual double to_f();
			virtual std::vector<Val>* to_array();
			virtual obj::Object* to_object();
			virtual ::Function* to_function();
	};

	class Int : public Empty {
		public :
			virtual std::string to_s();
			virtual int to_i();
			virtual int to_b();
			virtual double to_f();
			//virtual obj::Object* to_object();
			int val;
	};

	class Str : public Empty {
		public :
			virtual std::string to_s();
			virtual int to_i();
			virtual int to_b();
			virtual double to_f();
			std::string val;
	};

	class Float : public Empty {
		public :
			virtual std::string to_s();
			virtual int to_i();
			virtual int to_b();
			virtual double to_f();
			double val;	
	};

	class Array : public Empty {
		public :
			virtual std::vector<Val>* to_array();
			virtual int to_b();
			//virtual std::map<std::string, Val>* to_object();
			std::vector<Val>* array;
		
	};

	class Object : public Empty {
		public :
			//virtual std::string to_s();
			//virtual int to_b();
			//virtual std::vector<Val>* to_array();
			//virtual obj::Object* to_object();
			obj::Object* object;
			
			
	};
	
	class Function : public Empty {
		public :
			virtual ::Function* to_function();
			virtual std::string to_s();
			::Function* fun;
	};
}
#endif
