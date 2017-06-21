#include <stdlib.h>
#include <stdio.h>

size_t _strlen(const char *s);
size_t _strnlen(const char *s, size_t max_len);

char *_strchr(const char *s, int c);
char *_strrchr(const char *s, int c);

size_t _strlen(const char *s)
{
	size_t i = 0;
	while (s[i] != '\0')
		++i;
	return i;
}

size_t _strnlen(const char *s, size_t max_len)
{
	size_t i = 0;
	while (s[i] != '\0' && i < max_len)
		++i;
	return i;
}

char *_strchr(const char *s, int c)
{
	size_t i = 0;
	while (s[i] != c && s[i] != '\0')
		++i;
	return s[i] != '\0' ? (char*)(s + i) : NULL;
}

char *_strrchr(const char *s, int c)
{
	const size_t len = _strlen(s);
	int i = (int)len;
	while (i >= 0 && s[i] != c)
		--i;
	return i >= 0 ? (char*)(s + i) : NULL;
}

static void clear_input_buffer(void)
{
	char ch = 0;
	while(((ch = getchar()) !='\n') && (ch != EOF));
}

int main(void)
{
	char buf[256] = {'\0'};
	char chr = 0;
	char *result = NULL;
	printf("Write string: ");
	scanf("%s", buf);
	printf("Lenght of this string: %zu\n", _strlen(buf));
	printf("Test _strnlen() function for whole string: %zu\n",  
		_strnlen(buf, _strlen(buf)));
	printf("Test _strnlen() function for (lenght - 1) string: %zu\n",  
		_strnlen(buf, _strlen(buf) - 1));

	clear_input_buffer();

	printf("Write char, which you want to find in string: ");
	scanf("%c", &chr);
	result = _strchr(buf, chr);
	if (result)
		printf("Char '%c' was founded and begins from \"%s\"\n", 
			chr, result);
	else 
		printf("Char '%c' is not founded\n", chr);

	result = _strrchr(buf, chr);
	if (result)
		printf("Result of _strrchr(): \"%s\"\n", 
			result);
	else
		printf("_strrchr() also not found '%c'\n", chr);


	return EXIT_SUCCESS;
}
