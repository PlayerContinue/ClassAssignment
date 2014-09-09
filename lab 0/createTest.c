#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
//Create a text file containing one's and zero's
int main(int argc,char* argv){
	FILE *fp;
	int i;
	srand(time(NULL));
	fp = fopen("./test2.txt","w+");
	for(i=0;i<24;i++){
	   fputc((((rand()%10+1)%2)+48),fp);
	}
	fclose(fp);
}
