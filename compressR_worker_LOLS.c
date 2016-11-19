//child process code to be exec'd

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char* fileName = argv[1];
	int sizePart = atoi(argv[2]);
	int orderNum = atoi(argv[3]);
	int totalOffset = atoi(argv[4]);
	
	FILE *fp;
	fp = fopen(fileName, "r");
	fseek(fp, totalOffset, SEEK_SET);
	
	char input[sizePart];
	//fgets wasn't inclusive of the final character so we add one
	fgets(input, sizePart+1, fp);
	
	char output[sizePart];
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
	printf("\tWorker Output - PART %d: %s\n", orderNum, output);
	
	FILE* sampleOutput;
	//int fileNameLength = strlen(argv[1])-4;
	//char outputFile[fileNameLength+11];
	char outputFile[510];
	fileName[sizeof(fileName)- 4] = '_';
	snprintf(outputFile, 510, "%s_LOLS%d", fileName, orderNum);
	//strcpy(outputFile, fileName);
	//strcat(outputFile, "OUTPUT.txt");
	//outputFile[fileNameLength+10] = '\0';
	sampleOutput = fopen(outputFile, "w+");
	
	fputs(output,sampleOutput);
	fclose(fp);
	
	//success status is returned
	exit(0);
	//when would this process fail though?
	printf("\tWorker %d failed.\n", orderNum);
	return 0;
}
