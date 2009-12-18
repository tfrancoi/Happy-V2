CC = g++
BIN = bin/
SRC = src/
all : main

main : $(BIN)lexical.o $(BIN)Term.o $(BIN)preprocess.o 
	$(CC) -o $@ $^
	
$(BIN)lexical.o : $(SRC)lexical.cpp
	$(CC) -o $@ -c $^
	
$(BIN)preprocess.o : $(SRC)preprocess.cpp
	$(CC) -o $@ -c $^

$(BIN)Term.o : $(SRC)Term.cpp
	$(CC) -o $@ -c $^
	

	

	
clean:
	rm -rf $(BIN)/*.o
