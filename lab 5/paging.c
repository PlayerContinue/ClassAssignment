/*
	Programmer: David Greenberg
	Lab # 5: Paging
	
	Returns the page number and offset in a 32 bit memory given a location in virtual memory 
*/
#define MEM_SIZE 4
#define DEBUG 1
#include <stdlib.h>
#include <stdio.h>

//******************
//Prototypes
//******************
unsigned int computePage(unsigned int);
unsigned int computeOffset(unsigned int); 

//******************
//Functions
//******************
int main(int argc, char** argv){
	//Convert the argv value into an integer
	unsigned int address = strtol(argv[1],NULL,10);
	
	//print a message repeating the address
	printf("The address %u contains:\n", address);
	if(DEBUG == 1){
		perror(NULL);
	}
	//Print the message containing the page number
	printf("Page Number = %u\n", computePage(address));
	if(DEBUG == 1){
		perror(NULL);
	}
	//Print the messsage containing the offset
	printf("Offset = %u\n",computeOffset(address));
	if(DEBUG == 1){
		perror(NULL);
	}
	exit(0);
}

/*
		int address: The location in memory.
		returns: The page in memory
*/
unsigned int computePage(unsigned int address){
	
	return (address/(MEM_SIZE*1024));
	
}

/*
		int address: The location in memory.
		returns: The offset from the page in memory
*/
unsigned int computeOffset(unsigned int address){
	return (address%(MEM_SIZE*1024));
}
