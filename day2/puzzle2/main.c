#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

	int noun = 0;
	int verb = 0;
	int *fresh = (int*)malloc(size * sizeof(int));

	while(fresh[0] != 19690720) {
		memcpy(fresh, arr, size * sizeof(int));

		fresh[1] = noun;
		fresh[2] = verb;

		int done = 0;
		for(int i = 0; i <= size; i += 4) {
			switch(fresh[i]) {
				case 1:
					fresh[fresh[i + 3]] = fresh[fresh[i + 1]] + fresh[fresh[i + 2]];
					break;
				case 2:
					fresh[fresh[i + 3]] = fresh[fresh[i + 1]] * fresh[fresh[i + 2]];
					break;
				case 99:
					done = 1;
					break;
				default:
					done = 1;
					break;
			}

			if(done == 1) break;
		}

		verb += 1;
		if(verb > 99) {
			verb = 0;
			noun += 1;

			if(noun > 99) {
				printf("unable to find noun and verb combo\n");
				break;
			}
		}
	}

	printf("Output: %d\n", ((100 * fresh[1]) + fresh[2]));

	if(fclose(fp) != 0) return EXIT_FAILURE;

	if(line) free(line);
	if(arr) free(arr);
	if(fresh) free(fresh);

	return EXIT_SUCCESS;
}
