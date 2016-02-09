#include <stdio.h>
#define allSize 20
#define oddEvenSize 10


// Prototypes for methods
void calcEven(int* arrPtr, int length,int *sum,int *mean);
void calcOdd(int arr[], int length);


int main(){
	int arrAll [allSize];
	int arrEven [oddEvenSize];
	int arrOdd [oddEvenSize];
	int i=0, j=0, k=0;
	int sum =0, mean=0;
	//WHILE LOOP FILLS arAll with random numbers<10 distributes to arrOdd or arrEven
	for(i=0; i<20; i++){
		do{
			arrAll[i] = rand();
		}while(arrAll[i]>10||arrAll[i]<1);
		if(i%2==0){	//FILLS arrEven from even arrAll indexs
			arrEven[j] = arrAll[i];
			j++;
		}else{	//FILLS arrOdd from odd arrAll indexs
			arrOdd[k] = arrAll[i];
			k++;
		}
	}//end filling loop
	calcEven(arrEven, oddEvenSize, &sum, &mean);
	printf("arrEven Sum: %d Mean: %d\n", sum, mean);
	calcOdd(arrOdd, oddEvenSize);

	return 0;
}
void calcEven(int* arrPtr, int length,int *sum,int *mean){
	int i =0;
	for(i=0;i<length;i++){
		*sum = *sum + arrPtr[i];
	}
	*mean= *sum/length;
}
void calcOdd(int arr[], int length){
	int mean=0, sum =0;
	int i=0;
	for(i=0;i<length;i++){
		sum = sum + arr[i];
	}
	mean= sum/length;	
	printf("arrOdd Sum: %d Mean: %d\n",sum, mean);
}