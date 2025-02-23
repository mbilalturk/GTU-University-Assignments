all: clean compile run

compile: main.cpp os.cpp directory.cpp file.cpp link.cpp
	@g++ -o test main.cpp os.cpp directory.cpp file.cpp link.cpp

run:
	@./test

clean:
	@rm -f *.o
	@rm -f test
