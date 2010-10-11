#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <map>
#include "sem.h"

#define PUBLIC = 1
#define PRIVATE = 2

#define INNER_CLASS = 1
#define OUTER_CLASS = 2

class Type {
	public : 
		std::name;
		Type* heritFrom;
}

class Object {
	public :
		Object();
		get(std::string, const int CONTEXT);
		set(std::string, Val);
		define(std::string, const int ACCESS);
	
	private : 
		Type type;
		std::map<std::string, Val> values;
		std::map<std::string, int> accesses;
		
	
};

#endif
