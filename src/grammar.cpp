#include <iostream>
#include <vector>
#include "grammar.h"
#include "set/sets.h"



using namespace std;


string type[] = {
	"ERROR", "Programme", "Block_fun", "Fun",
	"fun", "Id", "Block_arg", "Instr", "Block_instr", "of", 
	"If", "While", "Call", "Assignement", "Return", "Skip",
	"set", "if", "while", "return", "skip", "Expr",
	"string", "int", "float"
};

const int type_length = 25;
const int nb_element_block = 2;
int element1_2[nb_element_block];

map<string, int> type_map;


map<int, int> regle1;
map<int, int> regle1_2;
map<int, sets> rewriteRule;
map<int, vector<Paire> > rule2;


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
	
	element1_2[0] = get_set_code("Block_fun");
	element1_2[1] =get_set_code("Block_instr");
	
	regle1_2[get_set_code("Block_fun")] = get_set_code("Block_fun");
	regle1_2[get_set_code("Block_instr")] = get_set_code("Block_instr");
}

/**
 * 0  pour n
 * -1 pour N
 */
void initRule2() {
	string tab1[] = {"Fun", "Block_fun"};
	string tab2[] = {"fun"};
	string tab3[] = {"Id"};
	string tab4[] = {"Block_arg"};
	string tab5[] = {"Instr", "Block_instr"};
	string tab6[] = {"skip"};
	string tab7[] = {"of"};
	string tab8[] = {"set"};
	string tab9[] = {"Expr"};
	string tab10[] = {"if"};
	string tab11[] = {"while"};
	string tab12[] = {"return"};
	
	vector<Paire> v1;
	v1.push_back(Paire(-1, create_sets(tab1, 2)));
	rule2[get_set_code("Programme")] = v1;
	rule2[get_set_code("Block_fun")] = v1;
	
	vector<Paire> v2;
	v2.push_back(Paire(1, create_sets(tab2, 1)));
	v2.push_back(Paire(1, create_sets(tab3, 1)));
	v2.push_back(Paire(1, create_sets(tab4, 1)));
	v2.push_back(Paire(1, create_sets(tab5, 2)));
	rule2[get_set_code("Fun")] = v2;
	
	
	vector<Paire> v3;
	v3.push_back(Paire(1, create_sets(tab6,1)));
	rule2[get_set_code("Skip")] = v3;
	
	vector<Paire> v4;
	v4.push_back(Paire(1, create_sets(tab7,1)));
	v4.push_back(Paire(0, create_sets(tab3,1)));
	rule2[get_set_code("Block_arg")] = v4;
	
	vector<Paire> v5;
	v5.push_back(Paire(-1, create_sets(tab5, 2)));
	rule2[get_set_code("Block_instr")] = v5;
	
	vector<Paire> v6;
	v6.push_back(Paire(1, create_sets(tab8, 1)));
	v6.push_back(Paire(1, create_sets(tab3, 1)));
	v6.push_back(Paire(1, create_sets(tab9, 1)));
	rule2[get_set_code("Assignement")] = v6;
	
	vector<Paire> v7;
	v7.push_back(Paire(1, create_sets(tab3, 1)));
	v7.push_back(Paire(0, create_sets(tab9, 1)));
	rule2[get_set_code("Call")] = v7;
	
	vector<Paire> v8;
	v8.push_back(Paire(1, create_sets(tab10, 1)));
	v8.push_back(Paire(1, create_sets(tab9, 1)));
	v8.push_back(Paire(2, create_sets(tab5, 2)));
	rule2[get_set_code("If")] = v8;
	
	
	vector<Paire> v9;
	v9.push_back(Paire(1, create_sets(tab11, 1)));
	v9.push_back(Paire(1, create_sets(tab9, 1)));
	v9.push_back(Paire(1, create_sets(tab5, 2)));
	rule2[get_set_code("While")] = v9;
	
	
	vector<Paire> v10;
	v10.push_back(Paire(1, create_sets(tab12, 1)));
	v10.push_back(Paire(1, create_sets(tab9, 1)));
	rule2[get_set_code("Return")] = v10;
	
	
	
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
		initRule2();
		initRewriteRule();	
}

int get_set_code(string t) {
	int result = type_map[t];
	if(!result) {
		cout << "ERROR : type " << t << " unknown" << endl;
	}
	return result;	
}


Paire::Paire(int nb, sets s) {
	this->s = s;
	this->nb = nb;
	
}



map<int, int> getRule1() {
	return regle1;
} 
map<int, int> getRule1_2() {
	return regle1_2;
}
map<int, vector<Paire> > getRule2() {
	return rule2;
}
map<int, sets> getRule3() {
	return rewriteRule;
}

int applyRule1_2(sets s) {
	return 0;
}
