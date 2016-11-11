#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int len = strlen(argv[1]);
	printf("LEN: %d\n", len);
	
	if(len < 3){
		printf("%s\n", argv[1]);
		return;
	}
	
	char input[len];
	strcpy(input, argv[1]);
	
	char output[len];
	char arrtmp[len];
	
	char tmp;
	int num = 1;
	
	int i;
	for(i=0;i < len ;i++)
	{
		if(input[i] == input[i+1] && input[i] == input[i+2])
		{
			tmp = input[i];
			num=3;
	
			for(i=i+2;i< len;i++)
			{
				
				if(input[i] == input[i+1])
					num++;
				else
				{
					memset(&arrtmp[0], 0, len);
					snprintf(arrtmp, len, "%d%c", num, tmp);
					strcat(output, arrtmp);
					break;
				}
			}
			
		}
		else
		{
			tmp = input[i];
			memset(&arrtmp[0], 0, len);
			snprintf(arrtmp, len, "%c", tmp);
			strcat(output, arrtmp);
			
		}
		printf("%s\n", output);
	}
	/*tmp = input[i];
	memset(&arrtmp[0], 0, len);
	snprintf(arrtmp, len, "%d", tmp);
	strcat(output, arrtmp);*/
	//printf("%s\n", output);
}
