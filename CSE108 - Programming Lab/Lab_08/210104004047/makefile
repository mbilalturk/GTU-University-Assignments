all: clean compile run

compile: lab08.c
	@gcc -o test lab08.c -lm

run:
	@./test

clean: 
	@rm -f *.o
	@rm -f test