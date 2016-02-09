#include <stdio.h>

int main(){
	int numbers [100];
	char letters [100];
	int num=0;
	int i =0;
	//Fill Numbers array
	for(i=0; i<100; i++){
		do{
			num = rand();
		}while(num>1000||num<1);
		numbers[i]=num;
	}
	//Fill Letters array
	for(i=0; i<100; i++){
		letters[i] = 'A'+rand()%26;
	}

	//Print Even Numbers Index
	for(i=1; i<100; i++){
		if(i%2==0){
			printf("numbers[%d] = %d\n",i,numbers[i]);
		}
	}
	//Print Even Letters Index
	for(i=1; i<100; i++){
		if(i%2==0){
			printf("letters[%d] = %c\n",i,letters[i]);
		}
	}
	return 0 ;
}