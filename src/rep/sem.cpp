#include <string>
#include <iostream>
#include <sstream>
#include "sem.h"
using namespace std;


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


Val::Val() {
	this->type = EMPTY;//empty
	this->val = new Empty();
}

Val::Val(int type, Value* v) {
	this->type = type;//empty
	this->val = v;
}

int Val::getType() {
	
	return this->type;
}

Val::Val(int val) {
	this->type = INTEGER;
	Int* i =  new Int();
	i->val = val;
	this->val = i;
}

Val::Val(double val) {
		this->type = REAL;
		Float* f = new Float();
		f->val = val;
		this->val = f;
}

Val::Val(string s) {
	this->type = STRING;
	Str* str = new Str();
	str->val = s;
	this->val = str;
} 

string Val::to_s() {
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


string Empty::to_s() {	
	return "(-)";
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
		

string Str::to_s() {
	return val;
}

int Str::to_i() {
	return 1;
}

int Str::to_b() {
	if(val == "") 
		return 0;
	else
		return 1;
}
double Str::to_f() {
	return 1.0;
}
