/**
Author: David Greenberg
Program: Launch.c
Class: Comp 322
Lab: 2
**/
#include <sys/wait.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Prototype functions
int splitChild(pid_t,int,char*[],char*[]);
int performWhenChild(int,char*[],char* env[]);
int performWhenParent(pid_t,int, char*[]);

//Launch function
int main(int argv, char* argc[],char* env[]){	
	pid_t child_parent;
	//Create a child process
	child_parent = fork();
	return splitChild(child_parent,argv,argc,env);
}

int splitChild(pid_t childOrParent,int argv,char* argc[], char* env[]){

	if(childOrParent==0){
	//current process is child	
		return performWhenChild(argv,argc,env);
	}else if(childOrParent==-1){
	//An error has occurred
		perror("ERROR: Child could not be created");
	}else{
	//Current process is parent
		return performWhenParent(childOrParent,argv,argc);
	}

}

//Perform when the process is the parent 
int performWhenParent(pid_t child_pid,int argv,char** argc){
	int status;
	int length;
	char *Buffer = malloc(sizeof(char)*3);
	//Print out value of file name
	if(argv>1){
		fprintf(stderr,"%s: $$ = ", argc[1]);
	}
	//Print child pid to the stderr
	length = sprintf(Buffer,"%d\n",child_pid);	
	write(2,Buffer,length);
	
	//wait for the child to complete it's process
	pid_t childId = waitpid(child_pid,&status,0);
	
	free(Buffer);
	Buffer = malloc(sizeof(char)*3);

	//Print out name of passed file	
	if(argv>1){
		fprintf(stderr,"%s: $? = ", argc[1]);
	}
	//Convert values to buffer
	length = sprintf(Buffer,"%d\n",status);	
	write(2,Buffer,length);
	
	return 0;
}

//Perform this function when the process is a child
int performWhenChild(int argv,char** argc, char* env[]){
	int i;
	char** newArgc = malloc(sizeof(char*)*(argv-2));
	//Create a new arrray for the commands	
	for(i=2;i<argv;i++){
		newArgc[i-2] = argc[i];
	}
	//Check for arguments
	if(argv > 1){
		//Execute the function
		execve(argc[1],newArgc,env);
	}
	return 5;
}

