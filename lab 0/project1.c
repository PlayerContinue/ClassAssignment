#define BUFFER_SIZE 8//1024
#define TOTALNUMBER 8
#define MAX_BUFFER_SIZE 1024
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
char* intToAscii(int);
char* binaryToAscii(char*,int);
void read_In_File(int);
char* parity(char*,int);
int parityValue(char*,int);

void printEight(char*, int, char*);

void hasFile(char*);
void noFile(currentValue);

int pad(int, char*);
char* tError(char*, int);
int npStrlen(char*);
char* removeString(char*,char);
int ngStrcomp(char*, char*);
//Main launch function
int main(int argc,char *argv[]){

	if(argc==1 || ngStrcomp(removeString(argv[1],'\n'),"-") == 0){
		//No file 
		
		currentValue currentValues;
		currentValues.bSize = 0;
		noFile(currentValues);
	 }else if(argc==2){
		//Only two, so check for file
		hasFile(argv[1]);
		return 0;
  }
}

void noFile(currentValue charList){
	charList.bSize = 0;
	read_In_File(0);
}

void hasFile(char* argv){
 int fd = open(argv,O_RDONLY);
    if(fd < 0){
      //Check if value is binary
      perror("FILE NOT FOUND!");
    }else{
      //Current segment is file type
      read_In_File(fd);
      }
}

void read_In_File(int fd){
	int bSize,i,toValue;
	char* Buffer = (char*) malloc(sizeof(char)*MAX_BUFFER_SIZE);
	char* binary = (char*) malloc(sizeof(char)*(TOTALNUMBER+1));
	
	bSize = read(fd,Buffer,MAX_BUFFER_SIZE);
	//Create a check to see if it was a human input
	bool checkForHuman = (Buffer[bSize-1]=='\n' ? false : true);
	printf("Original ASCII\t\tDecimal\tParity\tT-Error\n");
	printf("-------\t--------------\t-------\t-------\t-------\n");
	while(bSize > 0){
		//Remove extra values from end of file
		if(bSize%8!=0){
		 bSize--;
		}
		bSize = pad(bSize,Buffer);
		for(i=0;i<bSize;i+=TOTALNUMBER){
		printEight(Buffer,i,binary);
		 //Run value check
	   	 //Print out copy of values
	   	printf("%s ",binary);
		
		toValue = binaryToDecimal(binary,0);
	    
		//Print out as ASCII
	   	printf("%s\t\t",intToAscii(toValue));
	  
	    //Print out as Decimal
	    printf("%d\t",toValue);

	   	 //Print parity
	   	 printf("%s\t",parity(binary,0));
		
	    	//Print error
			printf("%s\n",tError(binary,0));
		}
		 
		if(checkForHuman == true){
		
		 bSize = read(fd,Buffer,MAX_BUFFER_SIZE);
		}else{
		 bSize = -1;
		 
		}	
		
	}
	//Clean up memory
	free(binary);
	free(Buffer);
}

//Remove a character from a string
char* removeString(char* s1, char s2){
	int size = sizeof(s1)/sizeof(s1[0]),i,j;
	char* Buffer = malloc(sizeof(char)*size); 
	for(i=0,j=0;i<size;i++){
		if(s1[i]!=s2){
			Buffer[j] = s1[i];
            		j++;
		}
	}
	return Buffer;
	
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

//Print the next eight value
void printEight(char* fullList, int start, char* eightChar){
	int i;
	int j;
	//char* eightChar = malloc(sizeof(char)*(TOTALNUMBER+1));
	
	for(i=start, j=0;i<start+TOTALNUMBER;i++,j++){
		if(fullList[i]!='1' && fullList[i]!='0'){
				j--;
				start++;
		}
		
		eightChar[j] = fullList[i];


	}
	eightChar[TOTALNUMBER] = '\0';
}

 
//Add 0 to the end of the list
int pad(int bSize,char* Buffer){
if(bSize>0 &&  bSize%TOTALNUMBER!=0){
	  int i;
    //If too small, then add zeros
    for(i=bSize; i<bSize + (TOTALNUMBER-(bSize%TOTALNUMBER));i++){
      Buffer[i] = '0';
    }
    	bSize +=(TOTALNUMBER-(bSize%TOTALNUMBER));
    }
   
    return bSize;
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
char* binaryToAscii(char* binLis,int startPos){
	int decimalValue = (binaryToDecimal(binLis,startPos));
	return intToAscii(decimalValue);
}

//Turn binary values into Ascii
char* intToAscii(int decimalValue){
  
  switch(decimalValue){
	  case 0: 
		  return "NUL \\0\0";
	  case 1:
		  return "SOH\0";
	  case 2:
		  return "STX\0";
	  case 3: 
		  return "ETX\0";
	  case 4: 
		  return "EOT\0";
	  case 5: 
		  return "ENQ\0";
	  case 6:
		  return "ACK\0";
	  case 7:
		  return "BEL '\\a'\0";
	  case 8:
		  return "BS '\\b'\0";
	  case 9: 
		  return "HT '\\t'\0";
	  case 10: 
		  return "LF '\\n'\0";
	  case 11:
		  return "VT  '\\v'\0";
	  case 12:
		  return "FF  '\\f'\0";
	  case 13:
		  return "CR  '\\r'\0";
	  case 14:
		  return "SO\0";
	  case 15: 
		  return "SI\0";
	  case 16: 
		  return "DLE\0";
	  case 17:
		  return "DC1\0";
	  case 18:
		  return "DC2\0";
	  case 19:
		  return "DC3\0";
	  case 20:
		  return "DC4\0";
	  case 21:
		  return "NAK\0";
	  case 22:
		  return "SYN\0";
	  case 23:
		  return "ETB\0";
	  case 24:
		  return "CAN\0";
	  case 25: 
		  return "EM\0";
	  case 26:
		  return "SUB\0";
	  case 27:
		  return "ESC\0";
	  case 28:
		  return "FS\0";
	  case 29:
		  return "GS\0";
	  case 30:
		  return "RS\0";
	  case 31:
		  return "US\0";
	  case 32: 
		  return "SPACE\0";
	  case 127:
		  return "DEL\0";
	  
  }
  char* point = malloc(sizeof(char)*2);
		  point[0] = (char) decimalValue;
		  point[1] = '\0';
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

   total=parityValue(binLis,start); 
   return ((total == 0) ? "False" : "True");
}

//get string length
int npStrlen(char* s){
	int i;
	for(i=0; s[i] != '\0';i++);
	return i;

}


