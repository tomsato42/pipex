#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("This is a program demonstrating the use of exit function.\n");

	// Some condition to exit the program
	if (1) {
		printf("Exiting the program with status code 0.\n");
		exit(0); // Exit the program with status code 0 (success)
	}

	// This code will not be executed
	printf("This line will not be printed.\n");

	return 0;
}
