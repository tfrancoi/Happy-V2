CC = g++ 
CCW = g++
BIN = bin/
SRC = src/
SET = set/
REP = rep/
LIB = lib/
all : happy

happy : $(BIN)main.o $(BIN)lexical.o $(BIN)Term.o $(BIN)preprocess.o $(BIN)sets.o $(BIN)grammar.o $(BIN)parser.o $(BIN)Prog.o $(BIN)interpreter.o $(BIN)expr.o $(BIN)sem.o $(BIN)instr.o $(BIN)standard.o $(BIN)reference.o 
	$(CCW) -o $@ $^
$(BIN)main.o : $(SRC)main.cpp
	$(CCW) -o $@ -c $^
$(BIN)lexical.o : $(SRC)lexical.cpp
	$(CCW) -o $@ -c $^
$(BIN)preprocess.o : $(SRC)preprocess.cpp
	$(CCW) -o $@ -c $^
$(BIN)Term.o : $(SRC)Term.cpp
	$(CCW) -o $@ -c $^
$(BIN)grammar.o : $(SRC)grammar.cpp
	$(CCW) -o $@ -c $^
$(BIN)parser.o : $(SRC)parser.cpp
	$(CCW) -o $@ -c $^
$(BIN)interpreter.o : $(SRC)interpreter.cpp
	$(CCW) -o $@ -c $^

$(BIN)sets.o : $(SRC)$(SET)sets.cpp
	$(CC) -o $@ -c $^
	
$(BIN)Prog.o : $(SRC)$(REP)prog.cpp 
	$(CCW) -o $@ -c $^
$(BIN)expr.o : $(SRC)$(REP)expr.cpp 
	$(CCW) -o $@ -c $^
$(BIN)sem.o : $(SRC)$(REP)sem.cpp 
	$(CCW) -o $@ -c $^
$(BIN)instr.o : $(SRC)$(REP)instr.cpp 
	$(CCW) -o $@ -c $^
	
$(BIN)standard.o : $(SRC)$(LIB)standard.cpp
	$(CCW) -o $@ -c $^
	
$(BIN)reference.o : $(SRC)$(LIB)reference.cpp
	$(CCW) -o $@ -c $^
clean:
	rm -rf $(BIN)/*.o
