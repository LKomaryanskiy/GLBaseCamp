#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


const int bits_in_int = sizeof(int) * 8;

static bool is_bit_set(int test_nmb, int bit_nmb)
{
	if (bits_in_int <= bit_nmb || 
		bit_nmb < 0) {
		printf("Error! Number must be positive and less than %d\n", 
								bits_in_int);
		return 0;
	} 
	
	return test_nmb & (0x1 << bit_nmb);
}

static void clear_input_buffer(void)
{
	char ch = 0;
	while(((ch = getchar()) !='\n') && (ch != EOF));
}

int main(void)
{
	int value = 0;
	int bit_nmb = 0;

	printf("Write a number: ");
	while(scanf("%i", &value) == 0) {
		printf("Error, write integer number: ");
		clear_input_buffer();
	} 

	printf("What bit do you want to test? ");
	while(scanf("%i", &bit_nmb) == 0 && (bits_in_int <= bit_nmb || 
		bit_nmb < 0)) {
		printf("Error, write integer number in range [0, %d]: ", 
								bits_in_int);
		clear_input_buffer();
	} 

	printf("The %d bit%s set in 1\n", bit_nmb, 
		is_bit_set(value, bit_nmb) ? "" : " not"  );

	return EXIT_SUCCESS;
}
