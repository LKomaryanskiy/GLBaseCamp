#include <stdlib.h>
#include <stdio.h>


void saving_calculator(){
	float miles = 0.0;
	float gasoline_cost = 1.0;
	float miles_per_gallon = 1.0;
	float parking = 0.0;
	float tolls = 0.0;
	float total_cost = 0.0;
	
	printf("Please, write total miles that You driven per day: ");
	scanf("%f", &miles);

	printf("How much does cost gallon of gasoline? ");
	scanf("%f", &gasoline_cost);

	printf("And how much miles your car can ride using one gallon? ");
	scanf("%f", &miles_per_gallon);
	
	printf("How much do You spend for parking? ");
	scanf("%f", &parking);

	printf("How much tolls do You pay per day? ");
	scanf("%f", &tolls);

	total_cost = miles * gasoline_cost / miles_per_gallon + parking + tolls;

	printf("You spend %4.2f$ per day.\n", total_cost);
};


int main(){
	saving_calculator();
	return EXIT_SUCCESS;
};
