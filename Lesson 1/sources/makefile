all: tasks

tasks: arithmetic.o calc.o
	gcc arithmetic.o -o arithmetic
	gcc calc.o -o calc

arithmetic.o: arithmetic.c
	gcc -c arithmetic.c 

calc.o: calc.c
	gcc -c calc.c

clean:
	rm *.o arithmetic calc
	
