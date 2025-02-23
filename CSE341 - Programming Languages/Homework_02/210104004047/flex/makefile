run: gpp_lexer
	./a.out

run_file: gpp_lexer
	./a.out input.g++ -v || exit 0

gpp_lexer: gpp_lexer.l
	flex -o gpp_lexer.c gpp_lexer.l  
	gcc gpp_lexer.c -lfl -o a.out

clean:
	rm -f gpp_lexer.c a.out