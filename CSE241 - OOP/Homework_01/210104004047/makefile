all: clean compile run

compile: main.cpp board.cpp
	@g++ -o test main.cpp board.cpp

run: 
	@./test

clean: 
	@rm -f *.o
	@rm -f test

