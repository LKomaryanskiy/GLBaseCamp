CC = gcc
CFLAGS = --std=c99 -Wall -Werror --pedantic -c
SOURCES =  	test_memset_pointer.c \
		func_access_by_pointer.c \
		std_func_twins.c \
		strlcpy.c \
		upper_lower.c

OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

EXECUTABLE = $(patsubst %.o,%,$(OBJECTS))

all: tasks

tasks: $(EXECUTABLE)

test_memset_pointer: test_memset_pointer.o
	$(CC) test_memset_pointer.o -o test_memset_pointer

func_access_by_pointer: func_access_by_pointer.o
	$(CC) func_access_by_pointer.o -o func_access_by_pointer

std_func_twins: std_func_twins.o
	$(CC) std_func_twins.o -o std_func_twins

strlcpy: strlcpy.o
	$(CC) strlcpy.o -o strlcpy

upper_lower: upper_lower.o
	$(CC) upper_lower.o -o upper_lower


#Compile without --pedantic
test_memset_pointer.o: test_memset_pointer.c
	$(CC) $(filter-out --pedantic, $(CFLAGS)) test_memset_pointer.c

#Compile without --pedantic
func_access_by_pointer.o: func_access_by_pointer.c
	$(CC) $(filter-out --pedantic, $(CFLAGS)) func_access_by_pointer.c

std_func_twins.o: std_func_twins.c
	$(CC) $(CFLAGS) std_func_twins.c

strlcpy.o: strlcpy.c
	$(CC) $(CFLAGS) strlcpy.c

upper_lower.o: upper_lower.c
	$(CC) $(CFLAGS) upper_lower.c


.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
