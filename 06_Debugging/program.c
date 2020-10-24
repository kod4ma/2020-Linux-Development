#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	char *arr = (char*)malloc(sizeof(char));
	printf("allocated char array of size 1\n");
	arr[0] = '@';
	printf("doing first free() ...\n");
	free(arr);
	printf("doing second free(), get ready for !@#$ ...\n");
	free(arr);
	return 0;
}
