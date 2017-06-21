#include <stdlib.h>
#include <string.h>

int main(void)
{
	unsigned char *pc = NULL;
	
	/* This line doesn't compile \
	 * with --pedantic parameter, \
	 * because ISO C forbids conversion \
	 * of function pointer to object \
	 * pointer type. 
	 */
	pc = (unsigned char*)(&memset);
	/* Error:
	 * from this address placed function \
	 * and we can't write any data. \
	 * Any trying to writings will give \
	 * segmentation fault.
	 */
	*pc = 0x90;
	return EXIT_FAILURE;
}
