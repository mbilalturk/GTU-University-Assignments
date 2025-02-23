CC = gcc
YACC = bison
LEX = flex
LIBS = -lfl

all: gpp_interpreter

gpp_interpreter: gpp_interpreter.tab.c lex.yy.c
	$(CC) -o gpp_interpreter gpp_interpreter.tab.c lex.yy.c $(LIBS)

gpp_interpreter.tab.c: gpp_interpreter.y
	$(YACC) -d -o gpp_interpreter.tab.c gpp_interpreter.y

lex.yy.c: gpp_lexer.l
	$(LEX) gpp_lexer.l

clean:
	rm -f gpp_interpreter gpp_interpreter.tab.c lex.yy.c gpp_interpreter.tab.h lex.yy.o

run: gpp_interpreter
	./gpp_interpreter

run_file: gpp_interpreter
	./gpp_interpreter input.g++