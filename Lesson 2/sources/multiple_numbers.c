/*Created by Leonid Komaryanskiy for GLBaseCamp*/

#include <stdio.h>
#include <stdlib.h>

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

int check_multiple(int fst_nmb, int sec_nmb)
{
	if (fst_nmb >= sec_nmb && sec_nmb != 0 && !(fst_nmb % sec_nmb))
		return 1;

	return 0;
}

void test(void)
{
	int fst_nmb = safe_read_int("Enter first integer number: ", "Please, write integer number!");
	int sec_nmb = safe_read_int("Enter second integer number: ", "Please, write integer number!");
	
	if (check_multiple(fst_nmb, sec_nmb))
		printf("%d is multiple of %d\n", fst_nmb, sec_nmb);
	else
		printf("%d isn't multiple of %d\n", fst_nmb, sec_nmb);
}

int main(void)
{
	test();
	return EXIT_SUCCESS;
}
