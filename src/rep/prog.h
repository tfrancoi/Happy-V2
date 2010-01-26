#include <string>
#include <map>
#include <vector>

class Instr {
	public:
		/**
		 * @return error code, 0 if nothing wrong happened.
		 */ 
		virtual int execute(Env*, Store*);
	
}

class Function {
	
	private :
		vector<Instr> instr;
		std::string name;
		int arity;
		
}

class Prog {
	public:
		Prog(Lterm* );
		int execute(std::string[] );
		Function* getFunction(std::string );
	private:
		map<std:string, Function*> functions;
	
	
};


class Expression {
	public :
		/**
		 * @param s : le tas, l'endroit ou les objets sont alloués dynamiquement
		 *        e : environement ou pile, l'endroit ou les variables qui sont dans le scope
		 * 				se voient attribuer une valeur
		 * @return un objet val qui représente la valeur renvoyée
		 */ 
		virtual Val eval(Store* s, Env* e);
}




class id : public Expression {
	private :
		string name;
		int ref;
	
}
