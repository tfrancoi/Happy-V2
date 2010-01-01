#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>


class Term {
	public :
		virtual int isTerminal();	
		virtual void print(int level);
};


class TTerm : public Term {
		public :
			virtual int isTerminal();	
			virtual void print(int level);
			TTerm();
			TTerm(std::string value, std::string type);
			~TTerm();
			std::string getType();
			std::string getValue();
			
		private :
				std::string value;
				std::string type;
		
};


class LTerm : public Term {
	public :
		virtual int isTerminal();	
		virtual void print(int level);
		LTerm();
		~LTerm();
		void add(Term *t);
		int size();
		Term* operator[](unsigned int i);
		void set(unsigned int i, Term* t);
		Term* flatten();
	private :
		std::vector<Term*> list;
 
};


#endif
