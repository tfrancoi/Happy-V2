#include <string>
#include <iostream>
#include <sstream>
#include "sem.h"

using namespace std;
using namespace rep;

/************************
 * 						*
 * 			Store		*
 * 						*
 ************************/
Store::Store() {
	store.push_back(Val());
}

Val Store::getVal(unsigned int adress) {
	if(adress >= store.size() || adress < 0) {
		cout << "Store index error, index out of range" << endl;
	}
	return store[adress];
}

unsigned int Store::newVal(Val v) {
	store.push_back(v);
	return store.size() - 1;
}
void Store::setVal(Val v, unsigned int adress) {
	if(adress >= store.size()) {
		cout << "Store index error, index out of range" << endl;
	}
	store[adress] = v;  			
}

/************************
 * 						*
 * 			Env			*
 * 						*
 ************************/
Env::Env(int nb_var) {
	tab = new Val[nb_var + 1];
	size = nb_var + 1;
}

Env::~Env() {
	delete tab;	
}

int Env::set(int index, Val value) {
	if(index < 0 || index >= this->size) 
		return 1;
	tab[index] = value;
	return 0;
}

int Env::set(int index, Val value, string name) {
	int error = set(index, value);
	if(error == 1)
		return error;
	names[name] = index + 1;
	return error;	
}

Val Env::get(int index) {
	if(index < 0 || index >= this->size) 
		return Val();//une valeur d'erreur
	
	return tab[index];
}

Val Env::get(string name) {
	int index = names[name];
	if(index == 0) 
		return Val();
	//cout << index << " " << endl;
	return tab[index - 1];
}

int Env::getSize() {
	return this->size;
}

/************************
 * 						*
 * 			Val			*
 * 						*
 ************************/
Val::Val() {
	this->type = EMPTY;//empty
	this->val = new Empty();
	this->ref = 0;
}

Val::Val(unsigned int ref) {
	this->type = REFERENCE;
	this->ref = ref;
	this->val = new Empty();
}

Val::Val(vector<Val> *v) {
	this->type = ARRAY;
	this->ref = 0;
	Array *ar = new Array();
	ar->array = v;
	this->val = ar;
}

Val::Val(GenericFunction* f) {
	this->type = FUNCTION;
	this->ref = 0;
	rep::Function* fun = new rep::Function();
	fun->fun = f;
	this->val = fun;
}
/*
Val::Val(map<string, Val> *v) {
	this->type = OBJECT;
	this->ref = 0;
	Object *o = new Object();
	o->object = v;
	this->val = o;
}*/

int Val::getType() {
	
	return this->type;
}

Val::Val(int val) {
	this->type = INTEGER;
	Int* i =  new Int();
	i->val = val;
	this->val = i;
	this->ref = 0;
}

Val::Val(double val) {
		this->type = REAL;
		Float* f = new Float();
		f->val = val;
		this->val = f;
		this->ref = 0;
}

Val::Val(string s) {
	this->type = STRING;
	Str* str = new Str();
	str->val = s;
	this->val = str;
	this->ref = 0;
} 

string Val::to_s() {
	if(type == REFERENCE) {
		return Val((int) ref).to_s();
	}
	return val->to_s();
}

int Val::to_i() {
	return val->to_i();
}

int Val::to_b() {
	return val->to_b();
}

double Val::to_f() {
	return val->to_f();
}

vector<Val>* Val::to_array() {
		return val->to_array();
}

unsigned int Val::get_ref() {
	return ref;
}

GenericFunction* Val::to_function() {
	return val->to_function();
}



/************************
 * 						*
 * 		Empty			*
 * 						*
 ************************/
string rep::Empty::to_s() {	
	return "(-> Empty <-)";
}

int rep::Empty::to_i() {
	return 0;
}

int rep::Empty::to_b() {
	return 0;
}

double rep::Empty::to_f() {
	return 0.0;
}

vector<Val>* rep::Empty::to_array() {
	return new vector<Val>();
}

obj::Object* Empty::to_object() {
	return NULL;
}

GenericFunction* Empty::to_function() {
	return NULL;
}
/************************
 * 						*
 *			Int			*
 * 						*
 ************************/
string rep::Int::to_s() {
	ostringstream out;
	out << this->val;
	return out.str();
	
}

int rep::Int::to_i() {
	return this->val;
}

int rep::Int::to_b() {
	return this->val;	
}


double rep::Int::to_f() {
	return this->val;
}

/************************
 * 						*
 * 		Float			*
 * 						*
 ************************/
string rep::Float::to_s() {
	ostringstream out;
	out << this->val;
	return out.str();
}

int rep::Float::to_i() {
	return (int) val;
}

int rep::Float::to_b() {
	if(val) 
		return 1;
	else
		return 0;
}

double rep::Float::to_f() {
	return val;
}
		
/************************
 * 						*
 * 			Str			*
 * 						*
 ************************/
string rep::Str::to_s() {
	return val;
}

int rep::Str::to_i() {
	return 1;
}

int rep::Str::to_b() {
	return val == "";
}
double rep::Str::to_f() {
	return 1.0;
}

/************************
 * 						*
 * 		Array			*
 * 						*
 ************************/
vector<Val>* rep::Array::to_array() {
	return array;
}

int rep::Array::to_b() {
	return array->size() > 0;
}

/************************
 * 						*
 * 		Object			*
 * 						*
 ************************/
/*
map<string, Val>* Object::to_object() {
	return object;
}*/


/************************
 * 						*
 * 		Function		*
 * 						*
 * **********************/
::GenericFunction* rep::Function::to_function() {
	return fun;
}

string rep::Function::to_s() {
	if(fun->getType() == NATIVE_FUNCTION) {
		return "Native Function";
	}
	else {
		function::Function* f = dynamic_cast<function::Function*>(fun);
		return f->getName();
	}
}
/*
string rep::Function::to_s() {
	return 
}*/
