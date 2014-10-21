/*
Programmer: David Greenberg
Lab: #4
Dining-Philosophers
Solve the dining philosophers problem using semephores
*/

#define sem_file sem_file
#define TERM 15
#define SIG_ERR (void (*)()) -1
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

//Prototypes
void think(char*,int*);
void eat(char*,int*);
void waitRand();
void startFunc(int argc, char** argv, int*,int*);
void killHandler(int);
int bool=1;

int main(int argc, char** argv){
//Keep track of eating and thinking
int totalThink=0;
int totalEat=0;
char* name;
  name = argv[2];

  if(argc<3){
    perror("Less than three arguments");
    exit(-1);
  }
  //Create kill signal handler
  if(signal(TERM,killHandler) == SIG_ERR){
      perror("ERROR: Couldn't created signal handler");
      exit(-1);
  }

  //Run the loop function
  startFunc(argc,argv,&totalThink,&totalEat);
  fprintf(stderr,"Philosopher #%s completed %d cycles\n",name,((totalThink + totalEat)/2));
  exit(0);
}


//Run the main function
void startFunc(int argc,char** argv,int* totalThink, int* totalEat){

char *letters2;
sem_t *right;
sem_t *left;
sem_t *crit;
  //Philosopher number
  char* p_num = argv[2];

  //Open left semaphore
  char letters[strlen(argv[2])+5];
  sprintf(letters,"/%stest",argv[2]);
  left = sem_open(letters,O_CREAT | O_EXCL,0666,1);
  perror(NULL);
  if(left==SEM_FAILED){
    left = sem_open(letters,O_CREAT,0666,1);
    perror(NULL);
  }

  crit = sem_open("/crit",O_CREAT | O_EXCL,0666,1);
  //perror(NULL);
  if(crit==SEM_FAILED){
    crit = sem_open("/crit",O_CREAT,0666,1);
    //perror(NULL);
  }

  int value = (atoi(argv[2]));

  //Open Right Semaphore
  if(value==1){
    //First philospher at the table
    letters2 = malloc(sizeof(char)*(strlen(argv[1])+5));
    sprintf(letters2,"/%stest",argv[1]);
    right = sem_open(letters2,O_CREAT | O_EXCL,0666,1);
    //perror(NULL);
    if(right==SEM_FAILED){
      right = sem_open(letters2,O_CREAT,0666,1);
      //perror(NULL);
    }
  }else{
    letters2 = malloc(sizeof(char)*(strlen(argv[1])+5));
    sprintf(letters2,"/%dtest",value-1);
    right = sem_open(letters2,O_CREAT | O_EXCL,0666,1);
    //perror(NULL);
    if(right==SEM_FAILED){
      right = sem_open(letters2,O_CREAT,0666,1);
      //perror(NULL);
    }
  }

  if(left==SEM_FAILED || right==SEM_FAILED){
    //Check for error
    perror("ERROR:SEM_ERROR");
  }

  //Signal wait cycle
  do{
  if(bool!=1){
	break;
  }
  sem_wait(crit);
  if(bool!=1){
	break;
  }

  sem_wait(left);
  if(bool!=1){
	break;
  }
  sem_wait(right);
  if(bool!=1){
	break;
  }
  eat(p_num,totalEat);
  sem_post(crit);
  sem_post(right);
  sem_post(left);

  if(bool!=1){
	break;
  }
  think(p_num,totalThink);

}while(bool==1);

if(sem_close(right)==-1){
	perror("ERROR: Fail");
	}
if(sem_close(left)==-1){
	perror("ERROR: Fail");
	}
  if(sem_close(crit)==-1){
	perror("ERROR: Fail");
	}
 if(sem_unlink(letters)==-1){
	perror("ERROR: Fail");
	}
if(sem_unlink(letters2)==-1){
	perror("ERROR: Fail");
	}
  if(sem_unlink("/crit")==-1){
	perror("ERROR: Fail");
	}

}

void killHandler(int signal){
	bool = 0;
}

void waitRand(){
  int random = rand()%1000000;
  usleep(random);
}
void eat(char* p_num,int* eatCycle){
  (*eatCycle)++;
  printf("Philosopher #%s is eating.\n", p_num);
  waitRand();

}

void think(char* p_num, int* thinkCycle){
  (*thinkCycle)++;
  printf("Philosopher #%s is thinking.\n", p_num);
  waitRand();

}
