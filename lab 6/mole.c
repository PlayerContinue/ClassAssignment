/*
Author: David Greenberg
Lab 6
Trivial program to print a line and die when killed
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


int main(int argc, char** argv){
	char cwd[1024];
	//Get the home directory
	struct passwd *pw = getpwuid(getuid());
	const char *hmedir = pw->pw_dir;	
	strcat(cwd,hmedir);
	strcat(cwd,"/lab6.log\0");

	//open the file

	FILE *fp = fopen(cwd,"a");
	if(fp==NULL){
		
	fp = fopen(cwd,"a");	
	}

	chmod(cwd,0666);
	
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
