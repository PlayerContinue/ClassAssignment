/*

Author: David Greenberg

File_Name: Matrix_add

Read a file and add a value to an matrix
*/
//#define DEBUGGING 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <aio.h>
#include <unistd.h>
#include <errno.h>
//******************************
//Prototypes
//******************************
void matrix_run(int block_size, int scalar, int size);
void matrix_add(char curBuffer[], int block_size,int scalar, char preBuffer[]);

//******************************
//Functions
//******************************

int main(int argc, char** argv, char** env){
	int size = atoi(argv[1]);
	size = size*size;
	int block = atoi(argv[2]);
	int block_size = size/block;
	srand(time(NULL));
	int scalar = rand()%200;
	
	matrix_run(block_size,scalar,size);
	
}


//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************
/*
Launch the current matrix read, write, and add procedure
*/
void matrix_run(int block_size, int scalar, int size){
	char curBuffer[block_size], previous[block_size];
	char next[block_size];
	int offset = 0; //Keep the current file offset
	int writeOffset = 0;
	time_t diffTime = time(NULL);
	//preset previous to empty
	previous[0] = '\0';
	
	//Create the request object
	struct aiocb* request = malloc(sizeof(struct aiocb));
	request->aio_buf = next;
	request->aio_fildes = 0;
	request->aio_nbytes = block_size;
	request->aio_offset = 0;
	
	//Create the response object
	struct aiocb* response = malloc(sizeof(struct aiocb));
	response->aio_buf = previous;
	response->aio_fildes = 1;
	response->aio_nbytes = block_size;
	response->aio_offset = 0;
	
	//Perform first request
	if(aio_read(request)!=0){
		perror("Read Error");
	}

	while(aio_error(request)==EINPROGRESS);

	if(aio_return(request)<0){
		perror("Return Error");
	}
	
		

	//Get the return from the read request
	do{
	memcpy(curBuffer,next,block_size);
	request->aio_offset = offset; // Set the offset
	//Create a read request
	if(aio_read(request)!=0){
		perror("Read Error");
	}
	offset = offset + block_size;

	#ifdef DEBUGGING
		printf("Size: %d, Block_size:%d, offset: %d\n",size,block_size,offset);
		perror(NULL);
	#endif
	
	#ifdef DEBUGGING
		printf("next: %s,curBuffer: %s\n",next, curBuffer);
	#endif
	
	matrix_add(curBuffer,block_size,scalar,previous);
	
	#ifdef DEBUGGING
		printf("previous: %s\n",previous);
	#endif	

	//Write the results currently stored to a file
	response->aio_offset = writeOffset;
	aio_write(response);
	while(aio_error(response)==EINPROGRESS);
	aio_return(response);
	writeOffset+=block_size;
	
	//Wait for progress
	while(aio_error(request)==EINPROGRESS);

	}while(aio_return(request)>0 && offset<=size);

	diffTime = diffTime - time(NULL);
	printf("Time Difference: %l\n",diffTime);
}


//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************
/*
Take the numbers out of the char array, convert to variables, and add the scalar
*/
void matrix_add(char curBuffer[], int block_size,int scalar, char previous[]){
	char numbers[10];
	int* matrix = malloc(sizeof(int)*block_size/3);
	int i =0, pos=0, bool =0; //counter for for loops
	//Break the value into a number
	for(i=0;i<block_size;i++){
		if((curBuffer[i]<='9' && curBuffer[i]>='0')|| curBuffer[i] == '-'){ //Add the current number, or negative symbol to the site
			numbers[pos]=curBuffer[i];			
			pos++;
		}else if(curBuffer[i]==','){
			numbers[pos] = '\0';
			*matrix = atoi(numbers) + scalar;
			if(bool == 1){
			 //Continue to add numbers to previous
			 sprintf(previous+strlen(previous),"%d,",*matrix);
			}else{
			 //Reset previous to empty for new writing
			 //Copy the value into the array
			 sprintf(previous,"%d,",*matrix);
			 bool =1;
			}
			
		#ifdef DEBUGGING
			printf("char: %s, matrix: %d\n",previous,*matrix);
		#endif
			matrix++;
			pos = 0;
		}
	}
	

}




