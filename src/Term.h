#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>
#include "set/sets.h"


class Term {
	public :
		virtual int isTerminal();	
		virtual void print(int level);
		int getType();
		sets getGeneral();
		void setType(int type);
		void setGeneral(sets gene);
	protected :
		int type; //spécifique
		sets general;
};


class TTerm : public Term {
		public :
			virtual int isTerminal();	
			virtual void print(int level);
			TTerm();
			TTerm(std::string value, std::string type, std::string file, int line);
			~TTerm();
			std::string getValue();
			
			
		private :
				std::string value;
				std::string file;
				int line;
		
};


class LTerm : public Term {
	public :
		virtual int isTerminal();	
		virtual void print(int );
		LTerm();
		~LTerm();
		void add(Term *);
		void del_last();
		int size();
		int isblock();
		Term* operator[](unsigned int );
		void set(unsigned int , Term* );
		Term* flatten();
		void set_type(int );
		
		void applyRule1();
	
	private :
		std::vector<Term*> list;
		int type;
		sets general;
 
};


#endif
