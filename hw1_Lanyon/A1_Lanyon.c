#include <stdio.h>
#include <math.h>

int main(){
	float small = 0.123;
	int large = pow(10,3);
	printf("small %.2f large %.2d \n", small, large);
	int * largePtr;
	float * smallPtr;
	largePtr = &large;
	smallPtr = &small; 
	*smallPtr = 0.33;
	*largePtr = pow(10,4);
	printf("small %.2f large %.2d \n", small, large); 
	printf("smallPtr %p largePtr %p \n", smallPtr, largePtr);
	//Do loop for small
	do{
		printf("Enter a number for small: ");
		scanf("%f", &small);
		if(small>1||small<0){
			printf("%.2f is not an acceptable value\n", small);
		}
	}while(small>1 || small<0);
	//DO loop for large
	do{
		printf("Enter a number for large: ");
		scanf("%d", &large);
		if(large>pow(10,6)||large<pow(10,3)){
			printf("%d is not an acceptable value\n", large);
		}
	}while(large>pow(10,6)||large<pow(10,3));
	return 0;
} 