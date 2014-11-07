/*
Author: David Greenberg
Lab 6
Trivial program to print a line and die when killed
*/

#include <stdio.h>

int main(int argc, char** argv){

	FILE *fp = fopen("~/lab6.log","w");
	fputs(argv[1],fp);

	while(1);
	
}
