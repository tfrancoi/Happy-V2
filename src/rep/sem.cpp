#include <string>
#include <iostream>
#include "sem.h"
using namespace std;


string types[] = {
	"empty", "integer"
};

const int types_length = 2;
map<string, int> types_map;


int getType(string s) {
	return types_map[s];
}


void initType() {	
	for(int i = 0; i < types_length; i++) {
		types_map[types[i]] = i;
	}
}

Env::Env(int nb_var) {
	tab = new Val[nb_var + 1];
	size = nb_var + 1;
}

int Env::set(int index, Val value) {
	if(index < 0 || index >= this->size) 
		return 1;
	tab[index] = value;
	return 0;
}

Val Env::get(int index) {
	if(index < 0 || index >= this->size) 
		return Val();//une valeur d'erreur
	
	return tab[index];
}


Val::Val() {
	this->type = ::getType("empty"); //empty
	this->val = Empty();
}

Val::Val(int val) {
	this->type = ::getType("integer");
	Int i = Int();
	i.val = val;
	this->val = i;
}

string Val::to_s() {
	return value.to_s();
}

String Value::to_s() {
	
	return "(-)";
}

String Int::to_s() {
	ostringstream out;
	out << this->val;
	return out.str();
	
}
