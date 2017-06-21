/*Created by Leonid Komaryanskiy for GLBaseCamp*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AMOUNT_OF_DIGITS 5

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

int is_palindrome(char *text)
{
	int result = 1;
	size_t i = 0;
	size_t length = 0;

	length = strlen(text);	
	while (i < length / 2 && result) {
		if (text[i] != text[length - 1 - i]) {
			result = 0;
		}
		++i;
	}		

	return result;
}

int is_five_digits_pal(int number)
{
	char buf[AMOUNT_OF_DIGITS + 1];
	sprintf(buf, "%d", number);
	if (strlen(buf) != AMOUNT_OF_DIGITS || !is_palindrome(buf))
		return 0;

	return 1;
}

void test(void)
{
	int number = 0;
	
	number = safe_read_int("Write five-digits integer number: ", \
							"Incorrect number!");
	if (is_five_digits_pal(number))
		printf("%5d is five digits palindrome\n", number);
	else
		printf("%5d isn't five digits palindrome\n", number);

}

int main(void)
{
	test();
	return EXIT_SUCCESS;
}
