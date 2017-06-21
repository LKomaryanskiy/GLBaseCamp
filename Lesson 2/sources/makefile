CC = gcc
CFLAGS = --std=c90 -Wall -Werror --pedantic -c 
OBJECTS = 	multiple_numbers.o \
			three_numbers.o \
			calc_BMI.o \
			palindrome_tester.o \
			find_smallest.o \
			calc_e.o \
			calc_PI.o

EXECUTABLE = $(patsubst %.o,%,$(OBJECTS))

all: tasks

tasks: $(EXECUTABLE)

multiple_numbers: multiple_numbers.o
	$(CC) multiple_numbers.o -o multiple_numbers

three_numbers: three_numbers.o
	$(CC) three_numbers.o -o three_numbers

calc_BMI: calc_BMI.o
	$(CC) calc_BMI.o -o calc_BMI

palindrome_tester: palindrome_tester.o
	$(CC) palindrome_tester.o -o palindrome_tester

find_smallest: find_smallest.o
	$(CC) find_smallest.o -o find_smallest

calc_e: calc_e.o
	$(CC) calc_e.o -lm -o calc_e 

calc_PI: calc_PI.o
	$(CC) calc_PI.o -lm -o calc_PI 


multiple_numbers.o: multiple_numbers.c
	$(CC) $(CFLAGS) multiple_numbers.c

three_numbers.o: three_numbers.c
	$(CC) $(CFLAGS) three_numbers.c

calc_BMI.o: calc_BMI.c
	$(CC) $(CFLAGS) calc_BMI.c

palindrome_tester.o: palindrome_tester.c
	$(CC) $(CFLAGS) palindrome_tester.c

find_smallest.o: find_smallest.c
	$(CC) $(CFLAGS) find_smallest.c

calc_e.o: calc_e.c
	$(CC) $(CFLAGS) calc_e.c

calc_PI.o: calc_PI.c
	$(CC) $(CFLAGS) calc_PI.c
	

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
