#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char delim = ',';

	int size = 0;
	int capacity = 10;
	int *arr = (int*)malloc(capacity * sizeof(int));

	while((read = getdelim(&line, &len, delim, fp)) != -1) {
		arr[size] = atoi(line);
		size++;

		if(size == capacity) {
			capacity *= 2;
			arr = (int*)realloc(arr, capacity * sizeof(int));
		}
	}
	printf("Size of arr: %d\n", size);

	arr[1] = 12;
	arr[2] = 2;

	int done = 0;
	for(int i = 0; i <= size; i += 4) {
		switch(arr[i]) {
			case 1:
				arr[arr[i + 3]] = arr[arr[i + 1]] + arr[arr[i + 2]];
				break;
			case 2:
				arr[arr[i + 3]] = arr[arr[i + 1]] * arr[arr[i + 2]];
				break;
			case 99:
				done = 1;
				break;
			default:
				printf("invalid input\n");

				if(line) free(line);
				if(arr) free(arr);

				return EXIT_FAILURE;
		}

		if(done == 1) break;
	}

	printf("Value at position 0 is: %d\n", arr[0]);

	if(fclose(fp) != 0) return EXIT_FAILURE;

	if(line) free(line);
	if(arr) free(arr);

	return EXIT_SUCCESS;
}
