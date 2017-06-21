#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* _strtolower(char* s, size_t len);
char* _strtoupper(char* s, size_t len);

char* _strtolower(char* s, size_t len)
{
	size_t i = 0;
	while (i < len && s[i] != '\0') {
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] |= 0x0020;
		++i;
	}
	return s;
}

char* _strtoupper(char* s, size_t len)
{
	size_t i = 0;
	while (i < len && s[i] != '\0') {
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] &= 0xffdf;
		++i;
	}
	return s;
}

int main(void)
{
	char buf[256] = {'\0'};
	printf("Write word, which you want to convert in lowercase: ");
	scanf("%s", buf);
	printf("Converted word: %s\n", _strtolower(buf, strlen(buf)));

	printf("Write word, which you want to convert in uppercase: ");
	scanf("%s", buf);
	printf("Converted word: %s\n", _strtoupper(buf, strlen(buf)));
	
	return EXIT_SUCCESS;
}
