all: clean compile run

compile: main.c util.c util.h
	@gcc -o test main.c util.c util.h

run: 
	@./test

clean:
	@rm -f *.o
	@rm -f test