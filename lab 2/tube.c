/**
Author: David Greenberg
Program: tube.c
Class: Comp 322
Lab: 2
**/
#define LOOPS 2
#define DEBUGLOOPS for(i=0;i<LOOPS;i++){ \
		for(k=0;toReturn2[0][i][k]!=NULL;k++){\
			\
			printf("[%d][%d]:%s\n",i,k,toReturn[i][k]);\
		}\
		printf("[%d][%d]:%s\n",i,k,toReturn[i][k]);\
	}
#define DEBUGLOOPS2 int k;\
		for(k=0;broken[childNumber][k]!=NULL;k++){\
			\
			fprintf(stderr,"[%d][%d]:%s\n",childNumber,k,broken[childNumber][k]);\
		}\
		fprintf(stderr,"[%d][%d]:%s\n",childNumber,k,broken[childNumber][k]);
		
#include <fcntl.h>              
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int* createPipe();
int breakByDelimiter(char****,char**,char*, int);
int splitChildren(int,char**,char**, pid_t, int,char***,int*,int);
int ngStrcomp(char*, char*);
int init(int,char**,char**);
void waitForProcess(pid_t, char***,int);
char* readFile(int);
int breakUp(char**, char***, char*, int);
int main(int argv, char* argc[],char* env[]){
	return init(argv,argc,env);
}

//Startup function for this program
int init(int argv,char* argc[], char* env[]){
  int i,toReturn;
int* pipefd;
 pid_t* loopBuffer = malloc(sizeof(pid_t)*LOOPS);
 pid_t child; 
char**** broken2 = malloc(sizeof(char***)*1);
int numExecs = breakByDelimiter(broken2,argc,",",argv);
char*** broken = broken2[0];
if(numExecs>1){
 //Allocate pipes: number of pipes = number of execs * 2
 pipefd = malloc(sizeof(int)*2*(numExecs-1));
 //Check for bad pipes
	 /*for(i=0;i<numExecs;i++){
		if(pipe(pipefd + (2*i))<0){
			perror("Couldn't create pipes");
		}
	}*/
	pipe(pipefd);
	}else{
		pipefd = NULL;
	}
	for(i=0;i<numExecs;i++){
		//Create a child
	        child = fork();
		loopBuffer[i] = child;
		
		//Break up function
		toReturn = splitChildren(argv,argc,env,child,i,broken,pipefd,numExecs);
		
	}
	//Close all the pipes
	for(i=0;pipefd!=NULL && i<numExecs;i++){	
			
			close(pipefd[i]);
		
	}
	//Go through all child processes and wait for them to finish
	if(child!=0){	
	waitForProcess(loopBuffer[i],broken,numExecs);
	
	
	}
	return toReturn;
}

//Split functions based on being child or adult
int splitChildren(int argv, char** argc, char** env,pid_t child, int childNumber, char** broken[],int* pipefd, int numChild){

	
	int i;
	if(child==0){
	 	//is a child process
		int pipeSize = (sizeof(pipefd)/sizeof(pipefd[0])); 
		if(pipefd!=NULL && childNumber < numChild-1){
		
		//Not last command, set child output to STDOUT		
			if(dup2(pipefd[(childNumber*2)+1],1)<0){
				perror("Unable to open out go pipe");
			}
		}else{
			close(pipefd[1]);
		}
	
		//If not the first child, set input to STDIN       
		if(pipefd!=NULL && childNumber!=0){
			if(dup2(pipefd[(childNumber*2)-2],0)<0){
				perror("Unable to open input pipe");
			}
			
				
		}else{
		  close(pipefd[0]);
		}	
		
		DEBUGLOOPS2
		if(execvp(broken[childNumber][0], broken[childNumber])==-1){
			perror("Failed to execute1\n");
		}
		//readFile(pipefd[(childNumber*2)-2]);
			
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
	fprintf(stderr,"File:%s\n",Buffer);
	return Buffer;
}

//Wait for process to finish
void waitForProcess(pid_t child, char*** broken,int numExecs){
		int status;
  //Wait for child to finish
        int i = 0,k;
	
	int childReturns[numExecs];
	while(waitpid(-1,&status,0) > 0){
		childReturns[i++] = status;
	}
	//Print out child status
	for(k=0;k<i;k++){
		
		fprintf(stderr,"%s: $? = %d\n", broken[k][0],childReturns[k]);
	
	}
}

//Break up a string or a set of string by a delimiter (Fix Function)
int breakByDelimiter(char**** toReturn2,char** string,char* delimiter,int length){
	int i,j,m,k,previousDelimiter;
	int returnInt;	
	char*** toReturn;
	//Count the number of the delimiter in the char array
	for(i=1;i<length;i++){
		if(ngStrcomp(string[i], delimiter)==0){
			j++;
		}
	}
	
	returnInt = j+1;
	toReturn = malloc(sizeof(char**)*(j+2));
	
	//Break the string in half based on the delimiter
	for(i=1,j=0,previousDelimiter=0;i<length;i++,previousDelimiter++){	

	if(ngStrcomp(string[i],delimiter)==0 || i==length-1){
		  //Create a new char** array either at end of string or when delimiter found
		  toReturn[j++] = malloc(sizeof(char**)*(previousDelimiter + 1));
		  toReturn[j-1][0] = NULL;
		  toReturn[j-1][previousDelimiter] = NULL;
		  previousDelimiter=0;
		}
	}
	
	//Store values in the string
	for(i=1,j=0,k=0;i<length;i++){
		if(ngStrcomp(string[i],delimiter)==0){
			j++;
			k=0;
		}else{
		 
		  toReturn[j][k++] = string[i];
		}
	
	}
	toReturn2[0] = toReturn;
	DEBUGLOOPS	
	//Return the number of children
	return returnInt;

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
int breakUp(char** lineIn, char*** lineOut, char* delimiter, int start){
	int toReturn=0,i=0;
	//Move lineIn to start Position
	*lineIn+=start;
	lineOut = malloc(sizeof(char**)*LOOPS);
	*lineOut = malloc(sizeof(char*)*LOOPS); 
	//Search for all non null values
	while(*lineIn != NULL){
		//Create a new array if a comma is found
		if(ngStrcomp(*lineIn,delimiter)){
			*lineOut++;
			*lineOut = malloc(sizeof(char*)*LOOPS);
		}
		**lineOut++ = *lineIn;
	}
	return LOOPS;
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



//Compare two strings
int ngStrcomp(char* s, char* t){
	int i;
	for (i = 0; s[i] == t[i]; i++){
		if (s[i] == '\0')
			return 0;
		
	}
	
	return s[i] - t[i];
	
}





