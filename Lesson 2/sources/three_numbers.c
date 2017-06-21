/*Created by Leonid Komaryanskiy for GLBaseCamp*/

#include <stdlib.h>
#include <stdio.h>

#define AMOUNT_OF_NUMBERS 3

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

int is_present(int number, int numbers[], size_t size)
{
	size_t i = 0;
	int result = 1;
	
	while (i < size && result) {
		if (numbers[i] == number)
			result = 0;
		++i;
	}

	return result;
}

int sum(int numbers[], size_t size)
{
	int result = 0;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
		result += numbers[i];

	return result;
}

float average(int numbers[], size_t size)
{
	float result = 0;
	if (size != 0)
		result = sum(numbers, size) / (float)size;

	return result;
}

int product(int numbers[], size_t size)
{
	int result = 1;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
		result *= numbers[i];

	return result;
}

int find_smallest(int numbers[], size_t size)
{
	int smallest = 0;
	if (size != 0) {
		size_t i = 0;
		smallest = numbers[0];
		
		for (i = 1; i < size; ++i) {
			if (numbers[i] < smallest)
				smallest = numbers[i];
		}
	}

	return smallest;
}

int find_largest(int numbers[], size_t size)
{
	int largest = 0;
	if (size != 0){
		size_t i = 0;
		largest = numbers[0];
		
		for (i = 1; i < size; ++i) {
			if (numbers[i] > largest)
				largest = numbers[i];
		}
	}

	return largest;
}

void all_tests(void)
{
	size_t i = 0;
	int buffer = 0;
	int numbers[AMOUNT_OF_NUMBERS] = {0};

	while (i < AMOUNT_OF_NUMBERS) {
		buffer = safe_read_int("Enter integer number: ", \
								"Please, write integer number!");			

		if (is_present(buffer, numbers, i)) {
			numbers[i] = buffer;
			++i; 
		} else
			printf("Write different number!\n");	
	}
	
	printf("\nSum: %d\n", sum(numbers, AMOUNT_OF_NUMBERS));
	printf("Average: %.3f\n", average(numbers, AMOUNT_OF_NUMBERS));
	printf("Product: %d\n", product(numbers, AMOUNT_OF_NUMBERS));
	printf("Smallest number: %d\n", find_smallest(numbers, AMOUNT_OF_NUMBERS));
	printf("Largest element: %d\n", find_largest(numbers, AMOUNT_OF_NUMBERS));
}

int main(void)
{
	all_tests();
	return EXIT_SUCCESS;
}
