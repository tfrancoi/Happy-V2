#include <string>
#include <iostream>
#include <sstream>
#include "sem.h"
using namespace std;

/************************
 * 											*
 * 				Store					*
 * 											*
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
 * 											*
 * 				Env						*
 * 											*
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

Val Env::get(int index) {
	if(index < 0 || index >= this->size) 
		return Val();//une valeur d'erreur
	
	return tab[index];
}

int Env::getSize() {
	return this->size;
}

/************************
 * 											*
 * 					Val					*
 * 											*
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

Val::Val(vector<Val> v) {
	this->type = ARRAY;
	this->ref = 0;
	Array *ar = new Array();
	ar->array = v;
	this->val = ar;
}

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

vector<Val> Val::to_array() {
		return val->to_array();
}

unsigned int Val::get_ref() {
	return ref;
}



/************************
 * 											*
 * 					Empty				*
 * 											*
 ************************/
string Empty::to_s() {	
	return "(-> Empty <-)";
}

int Empty::to_i() {
	return 0;
}

int Empty::to_b() {
	return 0;
}

double Empty::to_f() {
	return 0.0;
}

vector<Val> Empty::to_array() {
	return vector<Val>();
}

/************************
 * 											*
 * 					Int					*
 * 											*
 ************************/
string Int::to_s() {
	ostringstream out;
	out << this->val;
	return out.str();
	
}

int Int::to_i() {
	return this->val;
}

int Int::to_b() {
	return this->val;	
}


double Int::to_f() {
	return this->val;
}

/************************
 * 											*
 * 					Float				*
 * 											*
 ************************/
string Float::to_s() {
	ostringstream out;
	out << this->val;
	return out.str();
}

int Float::to_i() {
	return (int) val;
}

int Float::to_b() {
	if(val) 
		return 1;
	else
		return 0;
}

double Float::to_f() {
	return val;
}
		
/************************
 * 											*
 * 					Str					*
 * 											*
 ************************/
string Str::to_s() {
	return val;
}

int Str::to_i() {
	return 1;
}

int Str::to_b() {
	return val == "";
}
double Str::to_f() {
	return 1.0;
}

/************************
 * 											*
 * 					Array				*
 * 											*
 ************************/
vector<Val> Array::to_array() {
	return array;
}

int Array::to_b() {
	return array.size() > 0;
}
