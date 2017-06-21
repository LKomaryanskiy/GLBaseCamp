#include <stdlib.h>
#include <stdio.h>


static int claer_bits_by_mask(int val, int mask)
{
	return val & (~mask);
}

static void clear_input_buffer(void)
{
	char ch = 0;
	while(((ch = getchar()) !='\n') && (ch != EOF));
}

int main(void)
{
	int value = 0;
	int mask = 0;

	printf("Write a number: ");
	while(scanf("%i", &value) == 0) {
		printf("Error, write integer number: ");
		clear_input_buffer();
	} 

	printf("Write a mask, where you need to clear bits: ");
	while(scanf("%i", &mask) == 0) {
		printf("Error, write integer number: ");
		clear_input_buffer();
	} 

	printf("Value with applied mask: 0x%04x\n", claer_bits_by_mask(value, mask));

	return EXIT_SUCCESS;
}
