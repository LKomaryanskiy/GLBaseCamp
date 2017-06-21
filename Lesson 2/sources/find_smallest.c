/*Created by Leonid Komaryanskiy for GLBaseCamp*/

#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
	size_t pos;
	int value;
} elem_info;

int safe_read_int(char *text, char *error_mess)
{
	char buf[256] = {'0'};
	int error = 1;
	int result = 0;

	while (error) {	
		size_t i = 0;
		printf(text);
		fgets(buf, 256, stdin);
		error = 0;
		while (i < 256 && !error) { 
			if ((buf[i] < '0' || buf[i] > '9') && buf[i] != 10 && \
				buf[i] != '\0' && !(buf[i] == '-' && i == 0)) {
				printf("%s\n", error_mess);
				error = 1;
			}
			++i;
		}
	}
	
	sscanf(buf, "%i", &result);
	return result;
}

elem_info find_smallest(int *numbers, size_t size)
{
	elem_info smallest = {0, 0};
	if (size != 0) {
		size_t i = 0;
		smallest.value = numbers[0];
		smallest.pos = 0;
		
		for (i = 1; i < size; ++i) {
			if (numbers[i] < smallest.value) {
				smallest.value = numbers[i];
				smallest.pos = i;
			}
		}
	}

	return smallest;
}

void test(void)
{
	size_t amount_of_numbers = 0;
	size_t i = 0;
	int *numbers = NULL;
	elem_info result = {0, 0};

	while (amount_of_numbers <= 0) {
		int buf = 0;
		buf = safe_read_int("Enter sequence size: ", "Incorrect number!");
		if (buf <= 0)
			printf("Please, write positive number!\n");
		else
			amount_of_numbers = (size_t)buf;
	}
	
	numbers = (int*)malloc(sizeof(int) * amount_of_numbers);

	for (i = 0; i < amount_of_numbers; ++i)
		numbers[i] = safe_read_int("Enter number: ", "Please, write correct integer number");

	result = find_smallest(numbers, amount_of_numbers);
	printf("The smallest element has %lu and equal %d\n", result.pos, result.value);

	free(numbers);
}

int main(void)
{
	test();
	return EXIT_SUCCESS;
}
