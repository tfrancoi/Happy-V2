#include <string>
#include <iostream>
#include <sstream>
#include "sem.h"
using namespace std;


string types[] = {
	"empty", "integer", "string"
};

const int types_length = 3;
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
	this->val = new Empty();
}

int Val::getType() {
	
	return this->type;
}

Val::Val(int val) {
	this->type = ::getType("integer");
	Int* i =  new Int();
	i->val = val;
	this->val = i;
}

Val::Val(string s) {
	this->type = ::getType("string");
	Str* str = new Str();
	str->val = s;
	this->val = str;
} 

string Val::to_s() {
	return val->to_s();
}

string Value::to_s() {
	
	return "(-)";
}

string Int::to_s() {
	ostringstream out;
	out << this->val;
	return out.str();
	
}

string Str::to_s() {
	return val;
}
