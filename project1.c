#define BUFFER_SIZE 1024
#define TOTALNUMBER 8
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


typedef enum {false,true} bool;
typedef struct { 
	int bSize;
 	char* currentWord; 
} currentValue;


//Prototype
currentValue readIn(int fd);
int binaryToDecimal(char*, int);
char binaryToAscii(char*,int);
char* parity(char*,int);
int parityValue(char*,int);
char* printEight(char*, int);
void hasFile(char*);
void noFile(currentValue);
currentValue pad(int, char*);
//Main launch function
int main(int argc,const char *argv[]){
	
	if(argc==1 || argv[1] == "-"){
		//No file 
		char* currentValues = malloc(sizeof(char)*BUFFER_SIZE);
		scanf("%s",currentValues);
		int length = strlen(currentValues); 
		noFile((currentValue){length,currentValues});
	 }else if(argc==2){
		//Only two, so check for file
		hasFile(argv[1]);
		return 0;
  }
}

void noFile(currentValue charList){
	charList = pad(charList.bSize,charList.currentWord);
      int i = 0;
      while(i<charList.bSize){
	
	
	    //Run value check
	    //Print out copy of values
	    printf("%s ",printEight(charList.currentWord,i));

	    //Print out as ASCII
	    printf("%c ",binaryToAscii(charList.currentWord,i));
	  
	    //Print out as Decimal
	    printf("%d ",binaryToDecimal(charList.currentWord,i));

	    //Print parity
	    printf("%s\n",parity(charList.currentWord,i));
	  i+=8;
	
      }
}

void hasFile(char* argv){
 int fd = open(argv,O_RDONLY);
    if(fd < 0){
      //Check if value is binary
      perror("FILE NOT FOUND!");
    }else{
      //Current segment is file type
      currentValue charList = readIn(fd);
      int i = 0;
      while(i<charList.bSize){
	     printf("%d, %d\n", i, charList.bSize);
	
	    //Run value check
	    //Print out copy of values
	    printf("%s ",printEight(charList.currentWord,i));

	    //Print out as ASCII
	    printf("%c ",binaryToAscii(charList.currentWord,i));
	  
	    //Print out as Decimal
	    printf("%d ",binaryToDecimal(charList.currentWord,i));

	    //Print parity
	    printf("%s\n",parity(charList.currentWord,i));
	  i+=8;
	
      }
}
}

//Print the next eight value
char* printEight(char* fullList, int start){
	int i;
	
	char* eightChar = malloc(sizeof(char)*TOTALNUMBER);
	
	for(i=start;i<start+TOTALNUMBER;i++){
		eightChar[i-start] = fullList[i];
		if(fullList[i]=='\n'){
			printf("fail");
		}
	}
	return eightChar;
}






//Break the list of binary values into groups of eight
currentValue readIn(int fd){

  char *Buffer = malloc(sizeof(char)*BUFFER_SIZE);
  int bSize = read(fd,Buffer,BUFFER_SIZE);
 
	return pad(bSize,Buffer);

    
}
 
//Add 0 to the end of the list
currentValue pad(int bSize,char* Buffer){
if(bSize>0 &&  bSize%TOTALNUMBER!=0){
	  int i;
	  printf("%d %d\n",bSize,(bSize%TOTALNUMBER));
    //If too small, then add zeros
    for(i=bSize; i<bSize + (TOTALNUMBER-(bSize%TOTALNUMBER));i++){
      Buffer[i] = '0';
    }
    bSize +=(TOTALNUMBER-(bSize%TOTALNUMBER));
    }
  
    currentValue next = {bSize, Buffer};
    return next;
}

//Binary to Decimal
int binaryToDecimal(char* binLis,int startPos){
  int i,total,previous=2;
  total = binLis[startPos+(TOTALNUMBER-1)]-48;

  for(i=startPos+TOTALNUMBER-2;i>=startPos;i--){
    total += (binLis[i]-48)*previous;
    previous = previous*2;
  }
  return total;
}

//Turn binary values into Ascii
char binaryToAscii(char* binLis,int start){
  return (char)(binaryToDecimal(binLis, start)-binLis[start+(TOTALNUMBER-1)]-48);
  
}

//Get the parity update
char* parity(char* binLis, int start){
  int par = parityValue(binLis,start);
  if(par == 0){
    return "EVEN";
  }else{
    return "ODD";
  }
}
int parityValue(char* binLis, int start){
  int i,total;
  for(i=start;i<start + TOTALNUMBER;i++){
    total = binLis[i]-48;
  }
  
  return (total%2);



}

