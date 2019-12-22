#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *f = fopen("input.txt", "r");
	if(f == NULL) {
		exit(EXIT_FAILURE);
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	int fuelRequirment = 0;
	while((read = getline(&line, &len, f)) != -1) {
		int moduleMass = atoi(line);

		do {
			moduleMass = ((moduleMass / 3) - 2);
			if(moduleMass > 0) fuelRequirment += moduleMass;
		} while(moduleMass > 0);
	}
	printf("Fuel required: %d\n", fuelRequirment);

	if (fclose(f) != 0) {
		printf("error closing file\n");
	}

	if(line) {
		free(line);
	}

	return EXIT_SUCCESS;
}
