/*
Author: David Greenberg
Program: sprintd
Version: 0.0.1

A deamon which kills children processes and creates a new children process when called
*/
#define NUM_CHILD 2
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
//***************************
//Structs
//***************************
//Contains session id and children process ids
typedef struct{
	pid_t sid;
	pid_t* children;
} pidIdent; 

//***************************
//Global Variables
//***************************
pidIdent idents; //Contains SID and PID's for files

//***************************
//Prototypes
//***************************
void makeDaemon();
void createDaemon();
void daemonRun();
void whackAMoleSignal();
//***************************
//Functions
//***************************
int main(int argc, char** argv){
	
	
	createDaemon(&idents);
	whackAMoleSignal();
	daemonRun();

}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

/*
	Keep the daemon running

*/
void daemonRun(){
	srand(time(NULL));
	while(1){

		
	
	}

}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

/*
	Change the current process into a deamon
*/
void makeDaemon(pidIdent *ident){
	//Create local variables
	int i; //Counter for for loops
	
	
	//Create a new session (only this program in the file)
	ident->sid = setsid();
	
	if(ident->sid == -1){
		perror(NULL);
		exit(1);
	}
	
	//Change the directory to /
	if(chdir("/")==-1){
		perror(NULL);
		exit(1);
	}
	
	//Close all file Descriptors
	struct rlimit limit;
	if(getrlimit(RLIMIT_NOFILE,&limit)==-1){
	perror(NULL);
	}else if(limit.rlim_max == RLIM_INFINITY){
		limit.rlim_max = 1024;
	}
	
	for(i=3;i<limit.rlim_max;i++){
		if(close(i)==-1){
		}
	} 
	
	//Create location for children pid
	ident->children = malloc(sizeof(pid_t)*NUM_CHILD);
	
	//remap 0,1,2 to "/dev/null"
	int fd = open("/dev/null",O_RDWR);
	for(i=0;i<3;i++){
		if(dup2(i,fd)==-1){
			perror(NULL);
			exit(1);
		}
	}
}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

/*
	Create a daemon child
*/
void createDaemon(pidIdent* ident){

	//Change the permissions to be read, write, and execute
	umask(0);
	
	//Create the new process to become a daemon
	pid_t desc = fork();
	
	if(desc == 0){
		//Convert the child to a daemon
		makeDaemon(ident);
	}else if(desc == -1){
		//Failure has occured, throw an error and exit
		perror(NULL);
		exit(1);
	}else{
		printf("PID: %d",desc);
		//Currently in the parent, end the program succesfully
		exit(0);
	}
	
}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

//***************************
//Create Children
//***************************

void createMole(int child,const char* name){
	
	idents.children[child] = fork();
	fprintf(stderr,"%d\n",idents.children[child]);
	if(idents.children[child] == 0){
		//Convert to a mole
		char* temp[] = {"mole", name,NULL};
		if(execv("mole",temp)==-1){
		perror(NULL);
		exit(1);
	}
	}else if(idents.children[child] == -1){
		//Failure has occured, throw an error and exit
		perror(NULL);
		exit(1);
	}	
	}

//***************************
//Singal Handlers
//***************************

/*
 Handle the catching of sig_term. Kill all children and the process itself
*/
void handleSig_Term(int val){
	kill(idents.sid,SIGTERM);
	exit(0);
}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

/*
Catch SIG_User1. Kill mole1 then create a new mole if one does not exist in that slot
*/
void handleSig_User1(int val){
	//Kill the mole
	if(idents.children[0]!=0 && kill(idents.children[0],SIGKILL)==-1){
		perror(NULL);
		kill(idents.sid,SIGKILL);
		exit(1);
	}
	
	idents.children[0] = 0;
	
	//Create the new mole
	if(rand()%2==0){
		//Create mole1
		createMole(0,"mole1");
	}else{
		//Create mole2
		if(idents.children[1] == 0){
			createMole(1,"mole2");
		}
	}
}

//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

/*
Catch SIG_User2. Kill mole2
*/
void handleSig_User2(int val){
//Kill the mole
	if(idents.children[1]!=0 && kill(idents.children[1],SIGKILL)==-1){
		perror(NULL);		
		kill(idents.sid,SIGKILL);
		
		exit(1);
	}
	
	idents.children[1] = 0;
	
	//Create the new mole
	if(rand()%2==1){
		//Create mole1
		if(idents.children[0] == 0){
		createMole(0,"mole1");
		}
	}else{
		//Create mole2
		
			createMole(1,"mole2");
		
	}

}



//********************************************************************************************************
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************************

/*
Attach Signal's to their handlers
*/
void whackAMoleSignal(){
	if(signal(15,handleSig_Term)==SIG_ERR){
		perror(NULL);
		exit(1);
	}
	if(signal(10,handleSig_User1)==SIG_ERR){
		perror(NULL);
		exit(1);
	}
	if(signal(12,handleSig_User2)==SIG_ERR){
		perror(NULL);
		exit(1);
	}
}

