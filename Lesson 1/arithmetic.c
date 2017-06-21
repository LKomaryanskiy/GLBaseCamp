#include <stdlib.h>
#include <stdio.h>


void arithmetic(int first_nmb, int second_nmb){
	int sum = 0;
	int product = 0;
	int difference = 0;
	double quotient = 0.0;
	int remainder = 0;

	sum = first_nmb + second_nmb;
	product = first_nmb * second_nmb;
	difference = first_nmb - second_nmb;
	quotient = first_nmb / (double)second_nmb;
	remainder = first_nmb % second_nmb;	
	
	printf("Sum: %d\n", sum);
	printf("Product: %d\n", product);
	printf("Difference: %d\n", difference);
	printf("Quotient: %3.2f\n", quotient);
	printf("Remainder: %d\n", remainder);
};

void input_numbers(int* first_nmb, int* second_nmb){
	printf("Enter first number: ");
	scanf("%d", first_nmb);
	printf("Enter second number: ");
	scanf("%d", second_nmb);
};

int main(){
	int first_nmb = 0;
	int second_nmb = 0;
	input_numbers(&first_nmb, &second_nmb);
	arithmetic(first_nmb, second_nmb);
	return EXIT_SUCCESS;
};
