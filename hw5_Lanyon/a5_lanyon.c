/*************************************************
* Course: CS 4540 – Fall 2015
* Assignment 5
* Name: Justin Lanyon
* E-mail: justin.j.lanyon@wmich.edu
* Submitted: 12/11/2015
/*************************************************/

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

/*GLOBAL VARIABLES*/
int NR_THREADS = 10;
pthread_mutex_t count_mutex;
double circleCount=0;
int NR_PTS = 1000000;


/*Thread Function*/
void * threadFunction(){
	double x =0, y=0, threadPi =0, inCircle =0;
	int counter =0;
	pthread_t thrID	= pthread_self();
	unsigned seed = getpid() * time(NULL) * (thrID + 1);
	/*Loop till numPoints*/
	while(counter<(NR_PTS/NR_THREADS)){
		/*RANDOM X Y coordinate*/
		x =(rand_r(&seed)/(RAND_MAX +2.0));
		y =(rand_r(&seed)/(RAND_MAX +2.0));
		if((pow(x,2.0))+(pow(y,2.0)) <=1){
			//printf("%f , %f\n",x,y);
			inCircle++;
			pthread_mutex_lock(&count_mutex);
			circleCount++;
			pthread_mutex_unlock(&count_mutex);
		}/*END IF*/
		counter++;
	}/*END WHILE LOOP*/
	/*EXTRA CREDIT - CALCULATE THREAD ESTIMATE*/
	threadPi = 4 *inCircle/(NR_PTS/NR_THREADS);
	printf("Thread estimate for PI is : %f\n",threadPi);
}/*END THREAD FUNCTION*/

int main(){
	int i =0;
	double piEst=0;
	int err;
	pthread_t tid[NR_THREADS];
	/*Create mutex lock*/
	if (pthread_mutex_init(&count_mutex, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    /*Loop to create all threads*/
	while(i<NR_THREADS){
		err = pthread_create(&(tid[i]),NULL,&threadFunction,NULL);
		if(err !=0){
			printf("\ncan't create thread : %d\n",err);
		}
		i++;
	}
	i =0;
	/*Loop to join all threads*/
	while(i<NR_THREADS){
		pthread_join(tid[i], NULL);
		i++;
	}
	/*Destroy Mutex*/
	pthread_mutex_destroy(&count_mutex);
	/*Calculate PI estimate*/
	piEst = 4 *circleCount /  (NR_PTS);
	/*Print Pi estimate*/
	printf("The estimate for PI after combining all threads is: %f\n", piEst);
	printf("%d points were used in this estimation\n",NR_PTS);
	return 0;
}/*END MAIN*/