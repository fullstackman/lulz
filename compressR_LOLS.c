//Needs more code
//Ask and you shall receive..

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	//need to check if we have permission to access file
	FILE * fp;
	fp = fopen(argv[1], "r");
	
	//get size of text in file
	size_t pos = ftell(fp);
	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(fp);
	fseek(f, pos, SEEK_SET);
	
	//find size of parts
	int parts = atoi(argv[2]);
	int sizepart = fsize/parts;	//remember to account for remainder
	
	//here we should store the indeces to start and how much to do for each process
	//fork() "parts" number of parts
}
