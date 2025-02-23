all: clean compile run

compile: main.c
	@gcc -o test main.c -lm

run: 
	@./test

clean:
	@rm -f *.o
	@rm -f test