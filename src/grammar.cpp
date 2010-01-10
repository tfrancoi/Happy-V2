#include "grammar.h"
#include "set/sets.h"
#include <iostream>
using namespace std;


string type[] = {
	"ERROR", "Programme", "Block_fun", "Fun",
	"fun", "Id", "Block_arg", "Instr", "Block_instr", "of", 
	"If", "While", "Call", "Assignement", "Return", "Skip",
	"set", "if", "while", "return", "skip", "Expr",
	"string", "int", "float"
	
	};
int type_length = 25;

map<string, int> type_map;

map<int, int> regle1;
map<int, int> regle1_2;
map<int, sets> rewriteRule;


sets create_sets(string tab[], int size) {
	sets s;
	for(int i = 0; i < size; i++) {
		s.insert(get_set_code(tab[i]));
	}
	s.print();
	return s;
}

void initMap() {	
	for(int i = 0; i < type_length; i++) {
		type_map[type[i]] = i;
	}
}

void initRule1() {
	regle1[get_set_code("fun")] = get_set_code("Fun"); 
	regle1[get_set_code("skip")] = get_set_code("Skip");
	regle1[get_set_code("return")] = get_set_code("Return");
	regle1[get_set_code("set")] = get_set_code("Assignement");
	regle1[get_set_code("if")] = get_set_code("If");
	regle1[get_set_code("while")] = get_set_code("While");
	regle1[get_set_code("Id")] = get_set_code("Call");
	regle1[get_set_code("of")] = get_set_code("Block_arg");
	
	regle1_2[get_set_code("Block_fun")] = get_set_code("Block_fun");
	regle1_2[get_set_code("Block_instr")] = get_set_code("Block_instr");
}

void initRewriteRule() {
	string tab1[] = {"Instr", "Expr"};
	string tab2[] = {"Instr"};
	string tab3[] = {"Expr"};
	string tab4[] = {"Id", "Expr"};
	rewriteRule[get_set_code("Call")] = create_sets(tab1, 2);
	rewriteRule[get_set_code("Assignement")] = create_sets(tab1, 2);
	
	rewriteRule[get_set_code("If")] = create_sets(tab2, 1);
	rewriteRule[get_set_code("While")] = create_sets(tab2, 1);
	rewriteRule[get_set_code("Skip")] = create_sets(tab2, 1);
	rewriteRule[get_set_code("Return")] = create_sets(tab2, 1);
	
	rewriteRule[get_set_code("string")] = create_sets(tab3, 1);
	rewriteRule[get_set_code("float")] = create_sets(tab3, 1);
	rewriteRule[get_set_code("int")] = create_sets(tab3, 1);
	
	rewriteRule[get_set_code("Id")] = create_sets(tab4, 2);

}

void init() {
		initMap();
		initRule1();
		initRewriteRule();
	
}

int get_set_code(string t) {
	int result = type_map[t];
	if(!result) {
		cout << "ERROR : type " << t << " unknown" << endl;
	}
	return result;	
}
