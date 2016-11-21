//Needs more code

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

struct compParameters{
	char *fn;
	char *out;
	int sp;
	int off;
};

int compress(char *fileName, char *output, int sizePart, int totalOffset){
	
	FILE *fp;
	fp = fopen(fileName, "r");
	fseek(fp, totalOffset, SEEK_SET);
	
	char input[sizePart];
	//fgets wasn't inclusive of the final character so we add one
	fgets(input, sizePart+1, fp);
	
	output[0] = '\0';
	if(sizePart > 2){
		char arrtmp[2];
		int num = 1;
		int i;
		
		for(i=1; i<sizePart; ++i){
			if(input[i] != input[i-1]){
				switch(num){
					case 1:
						//print previous letter
						strncat(output, (char*) &input[i-1], 1);
						break;
					case 2:
						//print twice
						strncat(output, (char*) &input[i-1], 1);
						strncat(output, (char*) &input[i-1], 1);
						break;
					default:
						//print num times
						sprintf(arrtmp, "%d%c", num, input[i-1]);
						strcat(output, arrtmp);
				}
				num = 1;
			}
			else
				++num;
		}
		switch(num){
			case 1:
				//print previous letter
				strncat(output, (char*) &input[i-1], 1);
				break;
			case 2:
				//print twice
				strncat(output, (char*) &input[i-1], 1);
				strncat(output, (char*) &input[i-1], 1);
				break;
			default:
				//print num times
				sprintf(arrtmp, "%d%c", num, input[i-1]);
				strcat(output, arrtmp);
		}
	}
	else
		strcpy(output, input);
	printf("\tWorker Output: %s\n", output);
	
	return 0;
}



int main(int argc, char *argv[])
{
	if(argc > 3){
		printf("\tERROR: Too many parameters\n");
		return 99;
	}
	
	if(argc < 3){
		printf("\tERROR: Not enough parameters\n");
		return -1;
	}
	int numParts = atoi(argv[2]);
	if(!numParts){
		printf("\tERROR: incorrect number entered!\n");
		return -2;
	}
	
	//need to check if we have permission to access file
	FILE * fp;
	fp = fopen(argv[1], "r");
	
	if(fp == NULL){
		printf("\tERROR: That file was not found!\n");
		return 404;
	}
	
	int fileNameLength = strlen(argv[1])-4;
	char fileName[fileNameLength+1];
	strncpy(fileName, argv[1], fileNameLength);
	fileName[fileNameLength+1] = '\0';
	
	//get size of text in file
	fseek(fp, 0, SEEK_END);
	//ftell was giving us one too many!
	size_t fsize = ftell(fp) - 1;
	
	fclose(fp);
	
	//is user asking for more parts than there are characters?
	if(numParts > fsize){
		printf("\tERROR: Too many parts requested\n");
		return -1;
	}
	
	//find size of parts
	int sizePart = fsize/numParts;
	int offset = fsize % numParts;
	
	/* We can use this to delete the previous output files if the user calls this program on the same file multiple times!*/
	char* deleteCommand = malloc(43 + ( sizeof(char) * fileNameLength ) );
	sprintf(deleteCommand, "find -type f -name '%s_txt_LOLS*.txt' -delete", fileName);
	system(deleteCommand);
	
	char *output = malloc(fsize * sizeof(char));
	
	//here we should store the indeces to start and how much to do for each thread
	pthread_t pthreads[numParts];
	int i;
	for(i=0; i<numParts; i++)
	{
		//first part size is largest
		//includes any leftover characters
		/*struct compParameters para;
		para.fn = argv[1];
		para.out = output + ((i * sizePart) + offset);
		para.sp = sizePart;
		para.off = ((i * sizePart) + offset);
			
		pthreads[i] = pthread_create(pthreads[i], NULL, compress, compParameters);
		if(pthreads[i] == 0){
			//error
		}*/
		
		
		
		if(i == 0){		//if its the first part, increment by offset
			
			//put compress() args in a struct
			struct compParameters para;
			para.fn = argv[1];
			para.out = output;
			para.sp = sizePart + offset;
			para.off = 0;
				
			pthreads[i] = pthread_create(pthreads + i, NULL, compress, &para);
			if(pthreads[i] == 0){
				//error
			}
		}
		
		//put compress() args in a struct
		struct compParameters para;
		para.fn = argv[1];
		para.out = output + ((i * sizePart) + offset);
		para.sp = sizePart;
		para.off = ((i * sizePart) + offset);
			
		pthreads[i] = pthread_create(pthreads[i], NULL, compress, &para);
		if(pthreads[i] == 0){
			//error
		}
	}
	
	// wait for threads to finish working
	int j;
	for (j = 0; j < numParts; j++) {
		pthread_join(pthreads[j], NULL);
	}
	
	//create output file of compressed string
	FILE* sampleOutput;
	char outputFile[510];
	fileName[sizeof(fileName)- 4] = '_';
	snprintf(outputFile, 510, "%s_LOLS.txt", fileName);
	sampleOutput = fopen(outputFile, "w+");
	
	fputs(output,sampleOutput);
	fclose(fp);
	
	return EXIT_SUCCESS;
}

