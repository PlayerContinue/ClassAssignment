/*
Author: David Greenberg
Lab 6
Trivial program to print a line and die when killed
*/

#include <stdio.h>

int main(int argc, char** argv){

	FILE *fp = fopen("lab6.log\0","w+");
	if(fp==NULL){
		
	fp = fopen("lab6.log\0","w+");	
	}



if(fputs("Pop \0",fp)==EOF){
perror("work failed");

}

if(fputs(argv[1],fp)==EOF){
perror("work failed");

}

if(fputs("\n\0",fp)==EOF){
perror("work failed");

}
fflush(fp);
	while(1);
	
}
