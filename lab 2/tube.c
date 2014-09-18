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
void breakUp(char**, char***, char*, int);
int main(int argv, char* argc[],char* env[]){
	return init(argv,argc,env);
}

//Startup function for this program
int init(int argv,char* argc[], char* env[]){
  int i,toReturn;
 pid_t* loopBuffer = malloc(sizeof(pid_t)*LOOPS);
 pid_t child; 
char*** broken;// breakByDelimiter(argc,",",argv);
breakUp(argv,broken,",",1);
int* pipefd = malloc(sizeof(int)*2);
int success = pipe(pipefd);
	for(i=0;i<LOOPS;i++){
		//Create a child
	        child = fork();
		loopBuffer[i] = child;
		close(pipefd[i]);
		//Break up function
		toReturn = splitChildren(argv,argc,env,child,i,broken,pipefd);
		
	}

	//Go through all child processes and wait for them to finish
	
	waitForProcess(loopBuffer[i],broken,i);
		
	
	return toReturn;
}

//Split functions based on being child or adult
int splitChildren(int argv, char** argc, char** env,pid_t child, int childNumber, char** broken[],int* pipefd){
//Allocate a pipe 
	
	
	if(child==0){
	 //is a child process
	 
	if(childNumber == 0){
	
	  /* Set stdout to the output side of the pipe*/
        dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
        close(pipefd[0]);
       	char** test = broken[childNumber];
        execvp(test[0], test);

        perror("Failed to execute0\n");
	
        exit(0);
	}else{
	/* Set stdin to the input side of the pipe*/        
	dup2(pipefd[0], STDIN_FILENO);
	close(0);
	readFile(pipefd[0]);
	char** test = broken[childNumber];
        execvp(test[0], test);
       
	perror("Failed to execute1\n");
	close(pipefd[0]);
	close(pipefd[1]);
	
	
	exit(0);
	
	}
	}else if(child==-1){
	//Is an error
	perror("ERROR: A child could not be created");
	
	}else{

	//is a parent process
	//Print child pid
	fprintf(stderr,"%s: $$ = %d\n",broken[childNumber][0],child);
	//Close the pipe from the parents perspectice
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
        int i = 0;
	while(waitpid(-1,&status,0) > 0){
	//Print child status
	fprintf(stderr,"%s: $? = %d\n", broken[i][0],status);
	i++;
	}
}

//Break up a string or a set of string by a delimiter (Fix Function)
char*** breakByDelimiter(char** string,char* delimiter,int length){
	int i,j,m,k,previousDelimiter;
	char*** toReturn;	
	
	//Count the number of the delimiter in the char array
	for(i=1;i<length;i++){
		if(ngStrcomp(string[i], delimiter)==0){
			j++;
		}
	}
	
		
	toReturn = malloc(sizeof(char**)*(j+2));
	
	//Break the string in half based on the delimiter
	for(i=1,j=0,previousDelimiter=0;i<length;i++,previousDelimiter++){	

	if(ngStrcomp(string[i],delimiter)==0 || i==length-1){
		  //Create a new char** array
		 
		  toReturn[j++] = malloc(sizeof(char**)*(previousDelimiter+2));
		  toReturn[j-1][0] = 0;
		  toReturn[j-1][previousDelimiter+1] = 0;
		  previousDelimiter=0;
		}
	}

	for(i=1,j=0,k=0;i<length;i++){
		if(ngStrcomp(string[i],delimiter)==0){
			j++;
			k=0;
		}else{
		 
		  toReturn[j][k++] = string[i];
		}
	
	}
	
		
	//Return the arrays
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
//Breakup all values in the system
void breakUp(char** lineIn, char*** lineOut, char* delimiter, int start){
	//Move lineIn to start Position
	for(;start>0;start--){
		*lineIn++;
		}
	//Search for all non null values
	while(*lineIn != NULL){
		//Create a new array if a comma is found
		if(ngStrcomp(*lineIn,delimiter){
			*lineOut++;
		}
		**lineOut++ = *lineIn;
	}
}

//Parse a user line to a char array
void parse(char* line, char** argv){
	while(*line !='\0'){
		//Remove all white space
		while(*line ==' ' || *line == '\n' || *line == '\t'){
			*line++ = '\0';
		}
		*argv++ = line;
		//skip passed all whitespace
		while(*line ==' ' || *line == '\n' || *line == '\t'){
			*line++;
		}
	}
	*argv = '\0'; //The end of the arguments have been found
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





