/*

Author: David Greenberg

File_Name: Matrix_add

Read a file and add a value to an matrix
*/
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
int matrix_add(int curBuffer[], int block_size,int scalar, int preBuffer[]);

//******************************
//Functions
//******************************

int main(int argc, char** argv, char** env){
	if(argc<3){
		fprintf(stderr,"Too few arguments");
		exit(1);
	}	

	int size = atoi(argv[1]);
	size = size*size;
	int block = atoi(argv[2]);
	int block_size = size/block;
	srand(time(NULL));
	int scalar = rand()%200;

	if(block_size%4==0){
		matrix_run(block_size,scalar,size);
	}else{
		fprintf(stderr,"Too small to be an int");
	}
}	


//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************
/*
Launch the current matrix read, write, and add procedure
*/
void matrix_run(int block_size, int scalar, int size){
	int curBuffer[block_size], previous[block_size];
	int next[block_size];
	int offset = 0; //Keep the current file offset
	int writeOffset = 0, count=0, readOffset = 0;
	time_t diffTime = time(NULL);
		
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
	
	//Get the return from the read request
	do{
	memcpy(curBuffer,next,block_size);
	request->aio_offset = offset; // Set the offset
	//Create a read request
	if(aio_read(request)!=0){
		//perror("Read Error");
	}
	
	//Change the offsets
	offset = offset + readOffset;
	
	matrix_add(curBuffer,block_size,scalar,previous);
	
	//Write the results currently stored to a file
	response->aio_offset = writeOffset;
	response->aio_nbytes = readOffset;

	aio_write(response);
	
	while(aio_error(response)==EINPROGRESS);
	
	aio_return(response);
	
	writeOffset= writeOffset + readOffset;
	
	//Wait for progress
	//while(aio_error(request)==EINPROGRESS);
	
	readOffset= aio_return(request);

	}while(readOffset>0 && offset<=size);
	
	//Print end time
	diffTime = time(NULL)-diffTime;
	fprintf(stderr,"Time Difference: %d\n",(int)diffTime);
}


//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************
/*
Take the numbers out of the char array, convert to variables, and add the scalar

returns number of numbers
*/
int matrix_add(int curBuffer[], int block_size,int scalar, int previous[]){
	int i; //For loop
	for(i=0;i<block_size;i++){
		previous[i] = curBuffer[i] + scalar;
	}
}




