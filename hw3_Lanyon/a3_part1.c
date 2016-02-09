#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define arraySize 10000000
#define intConst 4

int main(){
	struct timespec start, finish;
	double elapsed;
	int * array =malloc(arraySize*sizeof(int));

	long int i=0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0; i<arraySize; i++){
		array[i]= intConst;
	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec)/1000000000.0;
	printf("Size of array %d with elapsed time: %f \n",arraySize,elapsed );
	return 0;
}