#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>


class Term {
	public :
		virtual int isTerminal();	
};


class TTerm : public Term {
		public :
			TTerm();
			TTerm(std::string value, std::string type);
			int isTerminal();
			~TTerm();
			std::string getType();
			std::string getValue();
			
		private :
				std::string value;
				std::string type;
		
};


class LTerm : public Term {
	public :
		LTerm();
		~LTerm();
		void add(Term t);
		int size();
		Term operator[](int i);
	private :
		std::vector<Term> list;
 
};


#endif
