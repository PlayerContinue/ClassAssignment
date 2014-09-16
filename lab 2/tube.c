/**
Author: David Greenberg
Program: tube.c
Class: Comp 322
Lab: 2
**/
#include <fcntl.h>              
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int* createPipe();
char*** breakByDelimiter(char**,char*);
int splitChildren(int,char**,char**, pid_t, int,char***);
int ngStrcomp(char*, char*);
int init(int,char**,char**);
int main(int argv, char* argc[],char* env[]){
	return init(argv,argc,env);
}

int init(int argv,char* argc[], char* env[]){
int childNumber = 0;
	//Create two children
	pid_t child1 = fork();
	//Break up function
	char*** broken = breakByDelimiter(argc,",");
	splitChildren(argv,argc,env,child1,0,broken);
	
	if(child1!=0){
		//Create second child only if not parent
		pid_t child2 = fork();
		splitChildren(argv,argc,env,child2,1,broken);
	}
	
	
	
	return 0;
}

int splitChildren(int argv, char** argc, char** env,pid_t child, int childNumber, char** broken[]){
//Allocate a pipe 
	int* pipefd = createPipe();
	
	if(child==0){
	 //Is a child process
	 
	}else if(child==-1){
	//Is an error
	perror("ERROR: A child could not be created");
	
	}else{
	//is a parent process
	//Print child pid
	fprintf(stderr,"%s: $$ = %d\n",broken[childNumber][0],child);
	//Close the pipe from the parents perspectice
	close(pipefd[0]);
	close(pipefd[1]);
	}
	

	
}

//Break up a string or a set of string by a delimiter
char*** breakByDelimiter(char** string,char* delimiter){
	int boolean = 0,i,j;
	int length = sizeof(string)/sizeof(string[0]);
	char** left_half = malloc(sizeof(char*)*2);
	char** right_half = malloc(sizeof(char*)*2); 	
	
	for(i=1,j=0;i<length;i++){
		if(boolean!=0 && ngStrcomp(string[i],delimiter)==0){
		  boolean = 1;
		  j=0;
		}else if (boolean == 0){
		  
		  left_half[j++] = string[i];
		printf("i: %s\n", left_half[j-1]);		
		}else{
		  right_half[j++] = string[i];
		}
	}
	char*** toReturn = malloc(sizeof(char**)*2);
	toReturn[0] = left_half;
	toReturn[1] = right_half;
	//Return the two arrays
	return toReturn;

}

//Create a new pipe, and test for failure
int* createPipe(){
	//Create an array
	int* pipefd = malloc(sizeof(int)*2);
	int success = pipe(pipefd);
	//Return on success, error otherwise
	if(success==0){
		return pipefd;
	}else{
		perror("ERROR: could not create a pipe");
	}
	return NULL;
}

//Compare to strings
int ngStrcomp(char* s, char* t){
	int i;
	
	for (i = 0; s[i] == t[i]; i++){
		if (s[i] == '\0')
			return 0;
	}
	
	return s[i] - t[i];
	
}
