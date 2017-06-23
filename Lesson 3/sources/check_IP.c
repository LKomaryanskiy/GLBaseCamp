#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	uint32_t ip;
	uint32_t network_address;
	uint32_t network_mask;
	
	bool is_part_of_network;
	bool is_correct_address;
} network_state;

static bool is_correct_address_str(char address[])
{
	bool result = true;
	size_t curr_part = 1;
	size_t i = 0;
	size_t curr_part_lenght = 0;

	const size_t length = strlen(address);
	const size_t parts = 4;
	const size_t max_part_length = 4;

	while (curr_part < parts && i < length && result)
	{
		++curr_part_lenght;


		if (!(isdigit(address[i]) || address[i] == '.') || \
			curr_part_lenght > max_part_length || curr_part >= parts)
			result = false;

		if (address[i] == '.') {
			++curr_part;
			curr_part_lenght = 0;
		} 

		++i;
	}

	if (curr_part != parts) 
		result = false;

	
	return result;
}

static uint32_t parse_address(char address[])
{
	uint32_t result = 0;
	int i = 0;
	size_t curr_byte = 3;
	const size_t length = strlen(address);

	while (i < length) {
		int j = 2;
		char buf_str[] = "000";
		uint32_t buf_uint = 0;
		size_t k = 0;

		while (i < length && address[i] != '.')
			++i;
		k = i;
		--i;
		
		while (i >= 0 && address[i] != '.') {
			buf_str[j] = address[i]; 
			--i;
			--j;
		} 
		i = k;
		
		sscanf(buf_str, "%ui", &buf_uint);
		result += (buf_uint << curr_byte * 8);
		--curr_byte;
		++i;
	}

	return result;
}

static bool is_part_of_network(network_state *ns)
{
	ns->is_part_of_network = (bool)
		!((ns->ip & ns->network_mask) ^ (ns->network_address)); 
	return ns->is_part_of_network;
}

static bool is_correct_address(network_state *ns)
{
	ns->is_correct_address = (bool)
		!(~(ns->network_mask) & (ns->network_address));
	return ns->is_correct_address;	
}

static void check_network_state(network_state *ns)
{
	is_correct_address(ns);
	if (ns->is_correct_address)
		is_part_of_network(ns);
	else
		ns->is_part_of_network = true;
}

static void clear_input_buffer(void)
{
	char ch = 0;
	while(((ch = getchar()) !='\n') && (ch != EOF));
}


int main(void)
{
	
	char buf[256];
	network_state ns;

	printf("Write ip address (for example: 192.168.0.0): ");
	scanf("%s", buf);
	while (!is_correct_address_str(buf)) {
		
		printf("Error, incorrect ip, try again: ");
		clear_input_buffer();
		scanf("%s", buf);
	}

	ns.ip = parse_address(buf);

	printf("Write network address (for example: 192.168.0.0): ");
	clear_input_buffer();
	scanf("%s", buf);
	while (!is_correct_address_str(buf)) {
		
		printf("Error, incorrect network address, try again: ");
		clear_input_buffer();
		scanf("%s", buf);
	}

	ns.network_address = parse_address(buf);

	printf("Write network mask (for example: 255.255.0.0): ");
	clear_input_buffer();
	scanf("%s", buf);
	while (!is_correct_address_str(buf)) {
		
		printf("Error, incorrect network address, try again: ");
		clear_input_buffer();
		scanf("%s", buf);
	}

	ns.network_mask = parse_address(buf);

	check_network_state(&ns);

	printf("This IP %s part of network",
		ns.is_part_of_network ? "is" : "isn't");
	
	printf("%s\n", \
		ns.is_correct_address ? "." : ", but pair of mask\\adress incorrect.");
	
	return EXIT_SUCCESS;
}
