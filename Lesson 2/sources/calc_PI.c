/*Created by Leonid Komaryanskiy for GLBaseCamp*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif


size_t safe_read_size_t(char *text, char *error_mess)
{
	char buf[256] = {'0'};
	int error = 1;
	size_t result;

	while (error) {	
		size_t i = 0;
		printf(text);
		fgets(buf, 256, stdin);
		error = 0;
		while (i < 256 && !error) { 
			if ((buf[i] < '0' || buf[i] > '9') && buf[i] != 10 && \
				buf[i] != '\0') {
				printf("%s\n", error_mess);
				error = 1;
			}
			++i;
		}
	}
		
	sscanf(buf, "%lu", &result);
	return result;
}

double calculate_pi(double accuracy)
{
	double ret_value = 4.0;
	int divider = 3;
	int sign = -1;
	printf("%1.16f\n", accuracy);
	while (fabs(M_PI - ret_value) > accuracy) {
		ret_value += (double)sign * 4.0 / (double)divider;
		divider += 2; 
		sign *= -1;
	}

	return ret_value;
}

void test(void)
{
	size_t accuracy = 0;
	
	while (accuracy < 1 || accuracy > 15) {
		accuracy = safe_read_size_t("Enter how much number of digits are significant (0 < n < 16):", 
					"Incorrect number!");
		if (accuracy < 1 || accuracy > 15)
			printf("Error, number must be more than 0 and less than 16!\n");
	}
	
	printf("Calculated PI is %1.16f\n", calculate_pi(pow(10.0, -1.0 * (double)accuracy)));
}

int main(void)
{
	test();
	return EXIT_SUCCESS;
}
