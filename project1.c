#define BUFFER_SIZE 8

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
typedef enum {false,true} bool;
//Prototype
char* readIn(int fd,int start);
bool isBinary(char*);
int binaryToDecimal(char*);
char binaryToAscii(char*);
char* parity(char*);
int parityValue(char*);
void hasFile();

//Main launch function
int main(int argc,const char *argv[]){
  if(argc==2){
    //Only two, so check for file
    hasFile(argv);
    return 0;
  }
}

void hasFile(char* argv[]){
 int fd = open(argv[1],O_RDONLY);
    if(fd < 0){
      //Check if value is binary
      perror("FILE NOT FOUND!");
    }else{
      //Current segment is file type
      char * charList = malloc(sizeof(char)*BUFFER_SIZE);
      int i = 0;
      while(charList!=NULL){
	charList = readIn(fd,BUFFER_SIZE*i);
	
	if(charList!=NULL){
	  //if(isBinary(charList)==true){
	    //Run value check
	    //Print out copy of values
	    printf("%s ",charList);

	    //Print out as ASCII
	    printf("%c ",binaryToAscii(charList));
	  
	    //Print out as Decimal
	    printf("%d ",binaryToDecimal(charList));

	    //Print parity
	    printf("%s\n",parity(charList));
	 // }else{
	    //Is not binary
	  //  printf("ERROR: Not a binary\n");
	 // }
	  i++;
	}
      }
}
}

//Check if value contained are only 1's and 0's
bool isBinary(char* posBin){
  int numberItems = sizeof(posBin)/sizeof(posBin[0]),i;
  for(i=0;i<BUFFER_SIZE;i++){
    if(posBin[i] !='0' && posBin[i] !='1'){
      return false;
    }
  }

  return true;
}




//Break the list of binary values into groups of eight
char* readIn(int fd, int start){
  int i;
  char *Buffer = malloc(sizeof(char)*BUFFER_SIZE);
  int bSize = read(fd,Buffer,BUFFER_SIZE);
  if(bSize>0 && bSize < BUFFER_SIZE){
    //If too small, then add zeros
    for(i=bSize;i<BUFFER_SIZE;i++){
      Buffer[i] = '0';
    }
    return Buffer;
  
  }else if(bSize <=0){
     return NULL;
    }

    
}
 


//Binary to Decimal
int binaryToDecimal(char* binLis){
  int i,total,previous=2;
  total = binLis[BUFFER_SIZE-1]-48;

  for(i=BUFFER_SIZE-2;i>=0;i--){
    total += (binLis[i]-48)*previous;
    previous = previous*2;
  }
  return total;
}
char binaryToAscii(char* binLis){
  return (char)binaryToDecimal(binLis);
  
}
char* parity(char* binLis){
  int par = parityValue(binLis);
  if(par == 0){
    return "EVEN";
  }else{
    return "ODD";
  }
}
int parityValue(char* binLis){
  int i,total;
  for(i=0;i<BUFFER_SIZE;i++){
    total = binLis[i]-48;
  }
  
  return (total%2);



}

