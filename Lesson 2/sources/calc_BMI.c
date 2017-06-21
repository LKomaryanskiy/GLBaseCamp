/*Created by Leonid Komaryanskiy for GLBaseCamp*/

#include <stdlib.h>
#include <stdio.h>

const char GRADES[4][20] = {"Underweight", "Normal", "Overweight", \
						"Obese"};

float safe_read_pos_real(char *text, char *error_mess)
{
	char buf[256] = {'0'};
	int error = 1;
	float ret_value = 0.0;

	while (error) {	
		size_t i = 0;
		printf(text);
		fgets(buf, 256, stdin);
		error = 0;
		while (i < 256 && !error) { 
			if ((buf[i] < '0' || buf[i] > '9') && buf[i] != 10 && \
				buf[i] != '\0' && buf[i] != '.') {
				printf("%s\n", error_mess);
				error = 1;
			}
			++i;
		}
	}
	
	sscanf(buf, "%f", &ret_value);
	return ret_value;
}

void print_inforamtion(void)
{
	printf("\n\tBMI VALUES\n");
	printf("Underweight: less than 18.5\n");
	printf("Normal: between 18.5 and 24.9\n");
	printf("Overweight: between 25 and 29.9\n");
	printf("Obese: 30 or greater\n");
	printf("-------------------------------\n");
}

float calculate_BMI(float weight, float height)
{
	return weight / (height * height);	
}

int get_BMI_type(float body_index)
{
	if (body_index < 18.5)
		return 0;
	if(body_index >= 18.5 && body_index < 25)
		return 1;
	if (body_index >= 25 && body_index < 30)
		return 2;
	
	return 3;
}

void print_results(float body_index)
{
	print_inforamtion();
	printf("Yours: %.2f - %s\n", body_index, GRADES[get_BMI_type(body_index)]);
}

int is_positive(float number)
{
	return number > 0.0;
}

void spot_personal_BMI(void)
{
	float weight = 0.0;
	float height = 0.0;
	float body_index = 0.0;
	
	while (!is_positive(weight))
		weight = safe_read_pos_real("Enter your weight in kilograms: ", 
							"Please, write positive number");	

	while (!is_positive(height))
		height = safe_read_pos_real("Enter your height in meters: ", 
						"Please, write positive number");


	body_index = calculate_BMI(weight, height);
	print_results(body_index);
}

int main(void)
{
	spot_personal_BMI();
	return EXIT_SUCCESS;
}
