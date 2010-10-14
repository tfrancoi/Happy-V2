#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <map>
#include "sem.h"

#define PUBLIC = 1
#define PRIVATE = 2

#define INNER_CLASS = 1
#define OUTER_CLASS = 2

class Val;

namespace obj {
	class Class {
		public :
			Class(Class* inherit);
			void define(std::string var_name, const int ACCESS);
		private :
			Class* heritFrom;			
			std::map<std::string, int> access;
	};
	
	class Object {
		public :
			Val get(std::string key, const int CONTEXT);
			bool set(std::string key, Val);
			
		
		private : 
			Class type;
			std::map<std::string, Val> values;		
	};
	
	
}

#endif
