/*

Author: David Greenberg
Create a matrix for use in matrix_add
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

//*******************************
//Prototypes
//*******************************
void createMatrix(int size);
int numberBetween(int min, int max);
void readMatrix(char** argv);
//*******************************
//Functions
//*******************************
int main(int argc, char** argv, char** env){

	if(argc > 1){
		if(strcmp(argv[1],"-b")!=0){
			createMatrix(atoi(argv[1]));
		}else if(argc>2){
			readMatrix(argv);
		}else{
			printf("Too Few Arguments");
		}
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
	int i,j;
	int integerVar[size];
		srand(time(NULL));
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
			   integerVar[j] = (rand()%2==0 ? numberBetween(0,100) : (-1*numberBetween(0,100)));
			}
			if(write(1, &integerVar,sizeof(int)*size)==-1){
				perror("Could not write");
			}
		}

		}
	//write(1,EOF,sizeof(int));
	int numberBetween(int min, int max){
	return (rand()%max);

}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************
/**
Read out the binary file as an integer file
**/
void readMatrix(char** argv){
	printf("Matrix is as follows:\n");
	int fd = open(argv[2],O_RDONLY);
		if(fd<0){
			perror("File Doesn't exist");
			exit(1);
		}

	int integerVar[1024];
	int i,j,length;	
	do{
		length = read(fd,integerVar,sizeof(int)*1024);
		for(j=0;j<length;j++){
			printf("%d,",integerVar[j]);
		}
		
	}while(length>0);
	close(fd);
}


