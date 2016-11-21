//Needs more code
//Ask and you shall receive..

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

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
	
	if(fp == NULL){
		printf("That file was not found!\n");
		return 404;
	}
	
	int fileNameLength = strlen(argv[1])-4;
	char fileName[fileNameLength+1];
	strncpy(fileName, argv[1], fileNameLength);
	fileName[fileNameLength+1] = '\0';
	printf("Here is the file name: %s\n",fileName);
	
	//get size of text in file
	//size_t pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	//ftell was giving us one too many!
	size_t fsize = ftell(fp) - 1;
	//fseek(fp, pos, SEEK_SET);
	
	fclose(fp);
	int numParts = atoi(argv[2]);
	
	//is user asking for more parts than there are characters?
	if(numParts > fsize){
		printf("ERROR: Too many parts requested\n");
		return -1;
	}
	
	//find size of parts
	int sizePart = fsize/numParts;
	int offset = fsize % numParts;
	
	/* We can use this to delete the previous output files if the user calls this program on the same file multiple times!
	char deleteCommand[2];
	sprintf(deleteCommand, "find -type f -name '%sOUTPUT*.txt' -delete", fileName);
	system(deleteCommand);*/
	
	//here we should store the indeces to start and how much to do for each process
	//fork() "parts" number of parts
	pid_t pids[numParts];
	int i;
	for(i=0; i<numParts; i++)
	{
		//first part size is largest
		//includes any leftover characters
		pids[i] = fork();
		
		if(pids[i] == 0){
			printf("PROCESS %d RUNNING\n", i);
			
			char sp[32];
			sprintf(sp, "%d", sizePart);
			
			char is[32];
			sprintf(is, "%d", i);
			
			
			
			if(i == 0){		//if its the first part, increment by offset
				
				char command[510];
				snprintf(command, 510, "./compressR_worker_LOLS %s %d %d %d", argv[1], (sizePart + offset), i, 0);
				execl("/bin/sh", "/bin/sh", "-c", command, NULL);
				//continue; 	<---not necessary
			}
			
			char command[510];
			snprintf(command, 510, "./compressR_worker_LOLS %s %d %d %d", argv[1], sizePart, i, ( (i * sizePart) + offset) );
			
			//char* command = "./compressR_worker_LOLS \"test.txt\" 2";
			execl("/bin/sh", "/bin/sh", "-c", command, NULL);
		}
		else{
			continue;
		}
	}
	
	//now we need to wait for each child process to finish working
	for(i=0; i<numParts; i++){
		int status;
		while ((pids[i] = wait(&status)) > 0)
		{
			printf("Exit status of %d was %d (%s)\n", (int)pids[i], status,
				   (status > 0) ? "reject" : "accept");
		}
	}
	return EXIT_SUCCESS;
}
