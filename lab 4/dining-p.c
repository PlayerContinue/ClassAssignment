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

//Prototypes
void think(char*,int*);
void eat(char*,int*);
void waitRand();
void startFunc(int argc, char** argv, int*,int*);
void killHandler(int);
int bool=1;
int totalThink=0;
int totalEat=0;
char* name;
int main(int argc, char** argv){
//Keep track of eating and thinking
  name= argv[2];

  if(argc<3){
    perror("Less than three arguments");
    exit(-1);
  }
  //Create kill term
  if(signal(TERM,killHandler) == SIG_ERR){
      perror("ERROR: Couldn't created signal handler");
      exit(-1);
  }

  startFunc(argc,argv,&totalThink,&totalEat);
}

char* letters;
char* letters2;
//Start everything
void startFunc(int argc,char** argv,int* totalThink, int* totalEat){
	sem_t *right;
	sem_t *left;
	sem_t *crit;
  //Philosopher number
  char* p_num = argv[2];
  char letters[strlen(argv[2])+5];
  sprintf(letters,"/%stest",argv[2]);
  left = sem_open(letters,O_CREAT,0666,1);
  crit = sem_open("/crit",O_CREAT,0666,1);

  int value = (atoi(argv[2]));

  if(value==1){
    char letters2[strlen(argv[1])+5];
    sprintf(letters2,"/%stest",argv[1]);
    right = sem_open(letters2,O_RDWR | O_CREAT,0666,1);
  }else{
    char letters2[strlen(argv[2])+5];;
    sprintf(letters2,"/%dtest",value-1);
    right = sem_open(letters2,O_RDWR | O_CREAT,0666,1);
  }

  if(left==SEM_FAILED || right==SEM_FAILED){
    //Check for error
    perror("ERROR:SEM_ERROR");

  }
  int checkCrit;
  //Signal wait cycle
  do{
  sem_wait(left);
  sem_wait(right);
  sem_wait(crit);
  eat(p_num,totalEat);
  sem_post(crit);
  sem_post(right);
  sem_post(left);
  think(p_num,totalThink);

}while(bool==1);


}

void killHandler(int signal){
  fprintf(stderr,"Philosopher #%s completed %d cycles\n",name,(totalThink + totalEat));
  sem_close(letters);
  sem_close(letters2);
  sem_close("/crit");
  sem_unlink(letters);
  sem_unlink(letters2);
  sem_unlink("/crit");
  exit(0);
}

void waitRand(){
  int random = rand();
  usleep(random);
}
void eat(char* p_num,int* eatCycle){
  *eatCycle++;
  printf("Philosopher #%s is eating.\n", p_num);
  waitRand();

}

void think(char* p_num, int* thinkCycle){
  *thinkCycle++;
  printf("Philosopher #%s is thinking.\n", p_num);
  waitRand();

}
