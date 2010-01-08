string type[] = {
	"Programme", "Block_fun", "Fun",
	"fun", "Id", "Block_arg", "Instr", "Block_instr", "of", 
	"If", "While", "Call", "Assignement", "Return", "Skip",
	"set", "if", "while", "return", "skip", "Expr",
	"string", "int", "float"
	
	}
int type_length = 24;

map<string, int> type_map;

void initMap() {
	
	for(int i = 0; i < type_length; i++) {
		type_map[type[i]] = i;
	}
}

void init() {
		initMap();
	
}

int getCode(string t) {
	return type_map[t];
	
}
