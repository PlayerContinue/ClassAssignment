/*
Author: David Greenberg
Current Version: 0.0.1
Finished State = 0%
*/
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdint.h>

void printValues(pid_t);

//Main funtion
int main(int argc, char* argv){
 
 pid_t pid;
//Fork a new process
  pid = fork();
  printValues(pid);
//Report values
  return 0;
//
}

//print function
void printValues(pid_t pid){
  struct tms localtime;
  clock_t currentTime;
  int status;
 

	if(pid == 0){//Is the child
    //Print process id and parent id
    printf("PPID: %d, PID: %d\n",(int)getppid(),(int)getpid());
	 
	
  }else if(pid==-1){
    perror("Failure occured. Could not create new fork."); 
  }else{ //is parent
 //Get current times
  currentTime = times(&localtime);
  //Print the length of time since...
    printf("Start: %d\n",(int)currentTime);
  pid_t childId;
  //Wait for child to finish
  childId =  waitpid(pid ,&status,0);
    //print PID, PPID, childId,return status
  printf("PPID: %d, PID: %d, CID: %d, RETVAL:%d\n",(int)getppid(),(int)getpid(),(int)childId, status); 
  //Print usertime, system time, cuser time, and csys time
    currentTime = times(&localtime);
     printf("USER: %d, SYS:%d\nCUSER: %d, CSYS: %d\n",(int)localtime.tms_utime,(int)localtime.tms_stime,(int)localtime.tms_cutime,(int)localtime.tms_cstime);
     printf("STOP: %d\n",(int)currentTime);
  }



}
