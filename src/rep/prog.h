#include <string>

class Prog {
	
	
	
}


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

class function {
	
	
}


class id : public Expression {
	private :
		string name;
		int ref;
	
}
