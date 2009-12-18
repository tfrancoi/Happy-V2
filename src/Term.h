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

#endif
