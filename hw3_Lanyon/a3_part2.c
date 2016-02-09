#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define arraySize 10000000

pthread_t tid[4];
int * array;


/*function for filling thread 1*/
void *fillArrayThread1(){
	int i=0;
	for(i=0;i<floor(arraySize/4)+1;i++){
		array[i]=0;
	}
	return NULL;
}
/*function for filling thread 2*/
void *fillArrayThread2(){
	int i=0;
	for(i=(floor(arraySize/4)+1);i<floor(arraySize/2)+1;i++){
		array[i]=1;
	}
	return NULL;
}
/*function for filling thread 3*/
void *fillArrayThread3(){
	int i=0;
	for(i=(floor(arraySize/2)+1);i<floor((3*arraySize)/4)+1;i++){
		array[i]=2;
	}
	return NULL;
}

/*function for filling thread 4*/
void *fillArrayThread4(){
	int i=0;
	for(i=(floor((3*arraySize)/4)+1);i<arraySize;i++){
		array[i]=3;
	}
	return NULL;
}

int main() {
	int i=0;
	int err;
	struct timespec start, finish;
	double elapsed;
	array = malloc(arraySize*sizeof(int));
	clock_gettime(CLOCK_MONOTONIC, &start);
	/*create thread 1*/
	err = pthread_create(&(tid[0]),NULL,&fillArrayThread1,NULL);
	if(err !=0){
		printf("\ncan't create thread : %d\n",err);
	}
	/*create thread 2*/
	err = pthread_create(&(tid[1]),NULL,&fillArrayThread2,NULL);
	if(err !=0){
		printf("\ncan't create thread : %d\n",err);
	}
	/*create thread 3*/
	err = pthread_create(&(tid[2]),NULL,&fillArrayThread3,NULL);
	if(err !=0){
		printf("\ncan't create thread : %d\n",err );
	}

	/*create thread 4*/
	err = pthread_create(&(tid[3]),NULL,&fillArrayThread4,NULL);
	if(err !=0){
		printf("\ncan't create thread : %d\n",err );
	}
	/*join all 4 threads*/
	pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec)/1000000000.0;
	printf("Size of array %d with elapsed time: %f \n",arraySize,elapsed );
	int j =0;

	return 0;
}