//Needs more code
//Ask and you shall receive..
//Be careful what you wish for...

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc > 3){
		printf("Don't give me so many parameters!\n");
		return 99;
	}
	
	if(argc < 3){
		printf("I'm gonna need more information...\n");
	}
	
	//need to check if we have permission to access file
	FILE * fp;
	fp = fopen(argv[1], "r");
	
	int fileNameLength = strlen(argv[1])-4;
	char fileName[fileNameLength+1];
	strncpy(fileName, argv[1], fileNameLength);
	fileName[fileNameLength+1] = '\0';
	printf("Here is the file name: %s\n",fileName);
	
	//get size of text in file
	size_t pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size_t fsize = ftell(fp);
	fseek(fp, pos, SEEK_SET);
	
	//find size of parts
	int parts = atoi(argv[2]);
	int sizepart = fsize/parts;	//remember to account for remainder
	printf("This is how many characters we can squeeze into each file: %d\n", sizepart);
	//here we should store the indeces to start and how much to do for each process
	//fork() "parts" number of parts
	
	fclose(fp);
	
	
	FILE* sampleOutput;
	char outputFile[fileNameLength+11];
	strcpy(outputFile, fileName);
	strcat(outputFile, "OUTPUT.txt");
	outputFile[fileNameLength+10] = '\0';
	sampleOutput = fopen(outputFile, "w+");
	char outputText[57];
	sprintf(outputText, "This is the number of parallel processes you requested: %d", parts);
	fputs(outputText,sampleOutput);
	fclose(fp);
	
	/* We can use this to delete the previous output files if the user calls this program on the same file multiple times!
	char deleteCommand[2];
	sprintf(deleteCommand, "find -type f -name '%sOUTPUT*.txt' -delete", fileName);
	system(deleteCommand);*/
	return 0;
}
