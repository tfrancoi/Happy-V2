CC = g++

all : main

main : lexical.o Term.o preprocess.o 
	$(CC) -o $@ $^
	
lexical.o : lexical.cpp
	$(CC) -o $@ -c $^
	
preprocess.o : preprocess.cpp
	$(CC) -o $@ -c $^

Term.o : Term.cpp
	$(CC) -o $@ -c $^
	

	

	
clean:
	rm -rf *.o
