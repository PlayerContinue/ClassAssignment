/**
Author: David Greenberg
Program: tube.c
Class: Comp 322
Lab: 2
**/
#define LOOPS 2
#include <fcntl.h>              
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int* createPipe();
char*** breakByDelimiter(char**,char*, int);
int splitChildren(int,char**,char**, pid_t, int,char***,int*);
int ngStrcomp(char*, char*);
int init(int,char**,char**);
void waitForProcess(pid_t, char***,int);
char* readFile(int);
int main(int argv, char* argc[],char* env[]){
	return init(argv,argc,env);
}

//Startup function for this program
int init(int argv,char* argc[], char* env[]){
  int i,toReturn;
 pid_t* loopBuffer = malloc(sizeof(pid_t)*LOOPS);
 pid_t child; 
char*** broken = breakByDelimiter(argc,",",argv);
int* pipefd = malloc(sizeof(int)*2);
int success = pipe(pipefd);
	for(i=0;i<LOOPS;i++){
		//Create a child
	        child = fork();
		loopBuffer[i] = child;
		//Break up function
		toReturn = splitChildren(argv,argc,env,child,i,broken,pipefd);
		//Leave loop if a child
		if(child==0){
		 break;	
		}
	}

	//Go through all child processes and wait for them to finish
	if(child!=0){
		for(i=0;i<LOOPS;i++){
	  	waitForProcess(loopBuffer[i],broken,i);
		}
	}
	return toReturn;
}

//Split functions based on being child or adult
int splitChildren(int argv, char** argc, char** env,pid_t child, int childNumber, char** broken[],int* pipefd){
//Allocate a pipe 
	
	
	if(child==0){
	 //is a child process
	 
	if(childNumber == 0){
	  /* Set stdout to the output side of the pipe*/
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        close(pipefd[0]);
        execv(broken[childNumber][0], broken[childNumber+1]);
        perror("Failed to execute0\n");
        exit(1);
	}else if(childNumber == 1){
		   /* Set stdin to the input side of the pipe*/
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        execv(broken[childNumber][0], broken[childNumber+1]);
        perror("Failed to execute1\n");
        
	exit(1);
	
	}
	}else if(child==-1){
	//Is an error
	perror("ERROR: A child could not be created");
	
	}else{

	//is a parent process
	//Print child pid
	fprintf(stderr,"%s: $$ = %d\n",broken[0][childNumber],child);
	//Close the pipe from the parents perspectice
	close(pipefd[0]);
	close(pipefd[1]);
	

	return 0;
	}


	
}

char* readFile(int fd){
	char* Buffer = malloc(sizeof(char)*1024);
	read(fd,Buffer,1024);
	fprintf(stderr,"%s\n",Buffer);
	return Buffer;
}

//Wait for process to finish
void waitForProcess(pid_t child, char*** broken,int childNumber){
		int status;
  //Wait for child to finish
        	
	waitpid(child,&status,0);
	//Print child status
	fprintf(stderr,"%s: $? = %d\n", broken[0][childNumber],status);
}

//Break up a string or a set of string by a delimiter
char*** breakByDelimiter(char** string,char* delimiter,int length){
	int boolean = 0,i,j,m;
	//int length = sizeof(string)/sizeof(string[0]);
	char** left_half = malloc(sizeof(char*)*3);
	char** right_half = malloc(sizeof(char*)*3); 	
	char** functions = malloc(sizeof(char*)*2);
	//Break the string in half based on the delimiter
	for(i=1,j=0,m=0;i<length;i++){
		if(m==0 || boolean==1 && m==1){
		  functions[m++] = string[i];
		  }
 	if(boolean==0 && ngStrcomp(string[i],delimiter)==0){
		  boolean = 1;
		  j=0;
		}else if (boolean == 0){
		  left_half[j++] = string[i];
		}else{
		  right_half[j++] = string[i];
		}
	}
	char*** toReturn = malloc(sizeof(char**)*2);
	toReturn[0] = functions;
	toReturn[1] = left_half;
	toReturn[2] = right_half;
	
	for(i=1;i<=2;i++){
	  if(toReturn[i][0]==NULL){
		toReturn[i][0] = "0";	
		} 
	}	
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


