CC = g++

all : main

main : bin/lexical.o bin/Term.o bin/preprocess.o 
	$(CC) -o $@ $^
	
bin/lexical.o : src/lexical.cpp
	$(CC) -o $@ -c $^
	
bin/preprocess.o : src/preprocess.cpp
	$(CC) -o $@ -c $^

bin/Term.o : src/Term.cpp
	$(CC) -o $@ -c $^
	

	

	
clean:
	rm -rf *.o
