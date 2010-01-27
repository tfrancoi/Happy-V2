CC = g++ 
CCW = g++ -Wall
BIN = bin/
SRC = src/
SET = set/
REP = rep/
all : main

main : $(BIN)main.o $(BIN)lexical.o $(BIN)Term.o $(BIN)preprocess.o $(BIN)sets.o $(BIN)grammar.o $(BIN)parser.o $(BIN)Prog.o
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

$(BIN)sets.o : $(SRC)$(SET)sets.cpp
	$(CC) -o $@ -c $^
	
$(BIN)Prog.o : $(SRC)$(REP)prog.cpp 
	$(CC) -o $@ -c $^
	
clean:
	rm -rf $(BIN)/*.o
