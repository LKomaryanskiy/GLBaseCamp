#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t strlcpy(char *d, const char *s, size_t dsize)
{
	size_t i = 0;
	while (i < dsize && s[i] != '\0') {
		d[i] = s[i];
		++i;
	}
	d[i] = '\0';

	return strlen(s);
}

static void clear_input_buffer(void)
{
	char ch = 0;
	while(((ch = getchar()) !='\n') && (ch != EOF));
}

int main(void)
{
	char buf1[256] = {'\0'};
	char buf2[256] = {'\0'};
	int dsize = 0;

	printf("Write string: ");
	scanf("%s", buf1);
	printf("Enter the number of first characters, which you want to copy: ");
	while (scanf("%i", &dsize) <= 0 || dsize < 0) {
		clear_input_buffer();
		printf("Error, write nonnegative integer value: ");
	}
	strlcpy(buf2, buf1, (size_t)dsize);
	printf("Second string: %s\n", buf2);

	
	return EXIT_SUCCESS;
}
