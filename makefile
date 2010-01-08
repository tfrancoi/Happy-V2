CC = g++ 
CCW = g++ -Wall
BIN = bin/
SRC = src/
SET = set/
all : main

main : $(BIN)main.o $(BIN)lexical.o $(BIN)Term.o $(BIN)preprocess.o $(BIN)sets.o
	$(CCW) -o $@ $^
	
$(BIN)main.o : $(SRC)main.cpp
	$(CCW) -o $@ -c $^

$(BIN)lexical.o : $(SRC)lexical.cpp
	$(CCW) -o $@ -c $^
	
$(BIN)preprocess.o : $(SRC)preprocess.cpp
	$(CCW) -o $@ -c $^

$(BIN)Term.o : $(SRC)Term.cpp
	$(CCW) -o $@ -c $^
	
$(BIN)sets.o : $(SRC)$(SET)sets.cpp
	$(CC) -o $@ -c $^

	
clean:
	rm -rf $(BIN)/*.o
