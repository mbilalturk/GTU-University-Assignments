all: clean1 clean2 compile1 run1 compile2 run2

compile1: main1.c 
	@gcc -o test1 main1.c -lm

run1:
	@./test1
clean1:
	@rm -f *.o
	@rm -f test1
	
compile2: main2.c
	@gcc -o test2 main2.c

run2: 
	@./test2

clean2: 
	@ rm -f *.o
	@rm -f test2	
