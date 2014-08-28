#define BUFFER_SIZE 8//1024
#define TOTALNUMBER 8
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//Typedef
typedef enum {false,true} bool;
typedef struct { 
	int bSize;
 	char* currentWord; 
} currentValue;


//Prototype
currentValue readIn(int fd);
int binaryToDecimal(char*,int);
char* binaryToAscii(char*,int);
char* parity(char*,int);
int parityValue(char*,int);
char* printEight(char*, int);
void hasFile(char*);
void noFile(currentValue);
currentValue pad(int, char*);
void output(currentValue);
char* tError(char*, int);
int npStrlen(char*);

//Main launch function
int main(int argc,char *argv[]){
	
	if(argc==1 || argv[1] == "-"){
		//No file 
		currentValue currentValues;
		//currentValues = readIn(0);
		getchar();
		noFile(currentValues);
	 }else if(argc==2){
		//Only two, so check for file
		hasFile(argv[1]);
		return 0;
  }
}

void noFile(currentValue charList){
	charList.bSize = 0;
	output(charList);
}




void hasFile(char* argv){
 int fd = open(argv,O_RDONLY);
    if(fd < 0){
      //Check if value is binary
      perror("FILE NOT FOUND!");
    }else{
      //Current segment is file type
	currentValue test = {fd,argv};
      output(test);
      }
}

//Output the given values
void output(currentValue charList){
	currentValue current;	
	int fd = charList.bSize;
	//current = readIn(fd);
	printf("Original ASCII\t\tDecimal\tParity\tT-Error\n");
	printf("-------\t--------------\t-------\t-------\t-------\n");
	
      while(current.bSize != -1){
	current = readIn(fd);
	if(current.bSize !=-1){
	    //Run value check
	    //Print out copy of values
	    printf("%s ",current.currentWord);
		
	    //Print out as ASCII
	    printf("%s\t\t",binaryToAscii(current.currentWord,0));
	  
	    //Print out as Decimal
	    printf("%d\t",binaryToDecimal(current.currentWord,0));

	    //Print parity
	    printf("%s\t",parity(current.currentWord,0));
		
	    //Print error
	    printf("%s\n",tError(current.currentWord,0));	
	    }
      }
}

//Print the next eight value
char* printEight(char* fullList, int start){
	int i;
	
	char* eightChar = malloc(sizeof(char)*TOTALNUMBER);
	
	for(i=start;i<start+TOTALNUMBER;i++){
		if(fullList[i]=='\n'){
			//Hotfix, figure out better option later
			fullList[i] = '1';
		}
		
		eightChar[i-start] = fullList[i];


	}
	
	return eightChar;
}






//Break the list of binary values into groups of eight
currentValue readIn(int fd){

  char *Buffer = malloc(sizeof(char)*BUFFER_SIZE);
  char *letter = malloc(sizeof(char)*1);
  int i;
  int bSize = read(fd,letter,1);
//Written to remove all non 1's, 0's
  for(i =0;i<BUFFER_SIZE && bSize !=0;i++){
	//Pull out values not 1 or zero
	if(letter[0] != '1' && letter[0] != '0'){
	//skip back and read last file
		i-=1;
	}else{
	 	Buffer[i] = letter[0];
	}
		bSize = read(fd,letter,1);	
	}

  //int bSize = read(fd,Buffer,BUFFER_SIZE);
	if(bSize==0 && i==0){
		return (currentValue){-1,Buffer};
	}else{
		return pad(npStrlen(Buffer),Buffer);
	}
}
 
//Add 0 to the end of the list
currentValue pad(int bSize,char* Buffer){
if(bSize>0 &&  bSize%TOTALNUMBER!=0){
	  int i;
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
	for(i=startPos+TOTALNUMBER-2;i>=startPos+1;i--){
		total += (binLis[i]-48)*previous;
		previous = previous*2;
	}
	return total;
}

//Turn binary values into Ascii
char* binaryToAscii(char* binLis, int startPos){
  int decimalValue = (binaryToDecimal(binLis,startPos));
  switch(decimalValue){
	  case 0: 
		  return "NUL \\0";
	  case 1:
		  return "SOH (start of heading)";
	  case 2:
		  return "STX (start of text)";
	  case 3: 
		  return "ETX (end of text)";
	  case 4: 
		  return "EOT (end of transmission)";
	  case 5: 
		  return "ENQ (enquiry)";
	  case 6:
		  return "ACK (acknowledge)";
	  case 7:
		  return "BEL '\\a' (bell)";
	  case 8:
		  return "BS '\\b' (backspace)";
	  case 9: 
		  return "HT '\\t' (horizontal tab)";
	  case 10: 
		  return "LF '\\n' (new line)";
	  case 11:
		  return "VT  '\\v' (vertical tab)";
	  case 12:
		  return "FF  '\\f' (form feed)";
	  case 13:
		  return "CR  '\\r' (carriage ret)";
	  case 14:
		  return "SO  (shift out)";
	  case 15: 
		  return "SI  (shift in)";
	  case 16: 
		  return "DLE (data link escape)";
	  case 17:
		  return "DC1 (device control 1)";
	  case 18:
		  return "DC2 (device control 2)";
	  case 19:
		  return "DC3 (device control 3)";
	  case 20:
		  return "DC4 (device control 4)";
	  case 21:
		  return "NAK (negative ack.)";
	  case 22:
		  return "SYN (synchronous idle)";
	  case 23:
		  return "ETB (end of trans. blk)";
	  case 24:
		  return "CAN (cancel)";
	  case 25: 
		  return "EM  (end of medium)";
	  case 26:
		  return "SUB (substitute)";
	  case 27:
		  return "ESC (escape)";
	  case 28:
		  return "FS  (file separator)";
	  case 29:
		  return "GS (group separator)";
	  case 30:
		  return "RS  (record separator)";
	  case 31:
		  return "US  (unit separator)";
	  case 32: 
		  return "SPACE";
	  case 127:
		  return "DEL";
	  
  }
  char* point = malloc(sizeof(char)*1);
		  point[0] = (char) decimalValue;
		  return point;
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
  int i,total=0;
  for(i=start;i<start + TOTALNUMBER;i++){
    total ^= binLis[i]-48;
  }
  return total;
}

//Check for Error
char* tError(char* binLis, int start){
   int i,total;
   total=parityValue(binLis,start)^(binLis[start]-48); 
   return ((total == (binLis[start]-48)) ? "True" : "False");
}

//get string length
int npStrlen(char* s){
	int i;
	for(i=0; s[i] != '\0';i++);
	return i;

}
