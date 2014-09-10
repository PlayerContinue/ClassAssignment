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
//Main funtion
int main(int argc, char* argv){
 struct tms localtime;
 clock_t currentTime;
 pid_t pid;
 int status;
  //Get current times
  currentTime = times(&localtime);
	

//Fork a new process
 
  pid = fork();
  if(pid == 0){//Is the child
    //Print process id and parent id
    printf("PID: %lu,PPID: %lu\n",getpid(),getppid());
  }else if(pid==-1){
    perror("Failure occured. Could not create new fork"); 
  }else{ //is parent
  //Print the length of time since...
    printf("Start: %jd\n",(intmax_t)currentTime);
  pid_t retval;
  //Wait for child to finish
  retval =  waitpid(pid ,&status,0);
    //print PID, PPID, childId,return status
  printf("PID: %lu,PPID: %lu, CID: %lu, RETVAL:%d\n",getpid(),getppid(),retval, status); 
  //Print usertime, system time, cuser time, and csys time
    currentTime = times(&localtime);
     printf("USER: %jd, SYS:%jd\nCUSER: %jd, CSYS: %jd\n",localtime.tms_utime,localtime.tms_stime,localtime.tms_cutime,localtime.tms_cstime);
     printf("STOP: %jd\n",currentTime);
  }

 
  getppid();
//Report values
  return 0;
//
}
