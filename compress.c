#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//printf("Enter your string. Repeated tmpters will be \"compressed\"");
	int len = strlen(argv[1]);
	printf("LEN: %d\n", len);
	
	char input[len];
	strcpy(input, argv[1]);
	char output[len];
	char arrtmp[len];
	//output[len-1] = '\0';
	
	char tmp;
	//char tmp2;
	int num = 1;
	
	int i;
	for(i=0;i < len ;i++)
	{
		if(input[i] == input[i+1] && input[i] == input[i+2])
		{
			tmp = input[i];
			num=3;
	
			for(i=i+2;i< len-1;i++)
			{
				
				if(input[i] == input[i+1])
					num++;
				else
				{
					//char tmp2[20];
					//itoa(tmp2, num, 10);
					//strcat(output, tmp2);
					//strcat(output, tmp);
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
			//output = output + tmp;
			//strcat(output, tmp);
			memset(&arrtmp[0], 0, len);
			snprintf(arrtmp, len, "%c", tmp);
			strcat(output, arrtmp);
			
		}
		printf("%s\n", output);
	}
	//output = output + num + tmp;
	//itoa(tmp2, num, 10);
	//strcat(output, tmp2);
	tmp = input[i];
	memset(&arrtmp[0], 0, len);
	snprintf(arrtmp, len, "%d", tmp);
	strcat(output, arrtmp);
	//strcat(output, tmp);
	printf("%s\n", output);
}
