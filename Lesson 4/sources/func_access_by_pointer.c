#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef void *(*func_t)(void *s, int c, size_t n);

volatile func_t memset_s = &memset;

int main(void)
{
	printf("memset_s address before calling: %p\n", (void*)memset_s);
	memset_s((void*)&memset_s, 0, sizeof(memset_s));
	printf("memset_s address after calling: %p\n", (void*)memset_s);
	return EXIT_SUCCESS;
}
