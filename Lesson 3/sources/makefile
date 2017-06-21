CC = gcc
CFLAGS = --std=c99 -Wall -Werror --pedantic -c
SOURCES =  	test_bit_set.c 	\
		clear_bits_by_mask.c \
		check_IP.c

OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

EXECUTABLE = $(patsubst %.o,%,$(OBJECTS))

all: tasks

tasks: $(EXECUTABLE)

test_bit_set: test_bit_set.o
	$(CC) test_bit_set.o -o test_bit_set

clear_bits_by_mask: clear_bits_by_mask.o
	$(CC) clear_bits_by_mask.o -o clear_bits_by_mask

check_IP: check_IP.o
	$(CC) check_IP.o -o check_IP


test_bit_set.o: test_bit_set.c
	$(CC) $(CFLAGS) test_bit_set.c

clear_bits_by_mask.o: clear_bits_by_mask.c
	$(CC) $(CFLAGS) clear_bits_by_mask.c

check_IP.o: check_IP.c
	$(CC) $(CFLAGS) check_IP.c



.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
