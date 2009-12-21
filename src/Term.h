#ifndef TERM_H
#define TERM_H

#include <string>

class Term {
		public :
			Term();
			Term(std::string value, std::string type);
			~Term();
			std::string getType();
			std::string getValue();
			
		private :
				std::string value;
				std::string type;
		
};

/*
class TList : public Term {
	public :
		TList();
		~TList();
		void add(Term t);
		int size();
		Term operator[](int i);
	private :
		vector<Term> list;
 
};
*/

#endif
