/*

Author: David Greenberg
Create a matrix for use in matrix_add
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
//*******************************
//Prototypes
//*******************************
void createMatrix(int size);
int numberBetween(int min, int max);
//*******************************
//Functions
//*******************************
int main(int argc, char** argv, char** env){

	if(argc > 1){
		createMatrix(atoi(argv[1]));
		#ifdef DEBUGGING
			perror(NULL);
		#endif
	}else{
		printf("Too Few Arguments");
	}

}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

/*
int size: The size of n in the n by n array
return: the matrix as an int[][]
*/
void createMatrix(int size){
	//Make random
	int i,j,var;
		srand(time(NULL));
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
					 //printf("%d,",(rand()%2==0 ? numberBetween(0,100) : (-1*numberBetween(0,100))));
						var = (rand()%2==0 ? numberBetween(0,100) : (-1*numberBetween(0,100)));
					 fwrite(1,var,sizeof(int));
			}
			//printf("\n");
		}
}

int numberBetween(int min, int max){
	return (rand()%max);

}


