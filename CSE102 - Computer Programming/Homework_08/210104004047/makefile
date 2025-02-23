all: clean compile run

compile: main.c
	@gcc -o test main.c

run: 
	@ulimit -s 64000 &&./test

clean:
	@rm -f *.o
	@rm -f test