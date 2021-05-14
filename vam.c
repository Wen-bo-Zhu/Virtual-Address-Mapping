/*
* @author Wenbo Zhu
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int my_stoi(char inputString[])
{
	int out = 0;
	for (unsigned int i = 0; i < strlen(inputString); i++)
	{
		int get;
		if (isdigit(inputString[i]))
		{
			get = inputString[i] - '0';
		}
		else if((inputString[i] >= 'A')&&(inputString[i] <= 'Z'))
		{
			get = inputString[i] - 'A' + 10;
		}
		else if((inputString[i] >= 'a')&&(inputString[i] <= 'z'))
		{
			get = inputString[i] - 'a' + 10;
		}
		out = out * 16 + get;
	}
	return out;
}

int main()
{
	char AllDatas[50][50];
	int AllDatasNum = 0;
	int TLBarray[4][20];
	int Pagearray[20];
	int Cachearray[20][50][4];
	char comparison[20];
	int i,j;
	FILE *in; 

	strcpy(comparison,"DONE");
	comparison[4] = 13;
	comparison[5] = '\n';
	comparison[6] = '\0';

	in = fopen("Project4Input.txt", "r");  	   
	while (1)
	{
		fgets(AllDatas[AllDatasNum], 100, in);
		if(strcmp(AllDatas[AllDatasNum], comparison) == 0)
		{
			break;
		}
		AllDatasNum++;
	}
	fclose(in); 
	for (i = 0; i<AllDatasNum; i++)
	{
		char getDatas[20][10] = {""};
		int flag = 0;
		int flag_2;
		for (j = 0; j<strlen(AllDatas[i]); j++)
		{
			if ((AllDatas[i][j] == '\0')||(AllDatas[i][j] == '\n')||(AllDatas[i][j] == 13))
			{
				break;
			}
			if (AllDatas[i][j] == ',')
			{
				flag++;
				continue;
			}
			flag_2 = strlen(getDatas[flag]);
			getDatas[flag][flag_2] = AllDatas[i][j];
			getDatas[flag][flag_2 + 1] = '\0';
		}
		flag++;

		for (j = 0; j<flag; j++)
		{
			if (strcmp(getDatas[j], "TLB") == 0)
			{
				TLBarray[my_stoi(getDatas[j + 1])][my_stoi(getDatas[j + 2])] = my_stoi(getDatas[j + 3]);
				j += 3;
				continue;
			}
			else if (strcmp(getDatas[j], "Page") == 0)
			{
				Pagearray[my_stoi(getDatas[j + 1])] = my_stoi(getDatas[j + 2]);
				j += 2;
				continue;
			}
			else if (strcmp(getDatas[j], "Cache") == 0)
			{
				Cachearray[my_stoi(getDatas[j + 1])][my_stoi(getDatas[j + 2])][0] = my_stoi(getDatas[j + 3]);
				Cachearray[my_stoi(getDatas[j + 1])][my_stoi(getDatas[j + 2])][1] = my_stoi(getDatas[j + 4]);
				Cachearray[my_stoi(getDatas[j + 1])][my_stoi(getDatas[j + 2])][2] = my_stoi(getDatas[j + 5]);
				Cachearray[my_stoi(getDatas[j + 1])][my_stoi(getDatas[j + 2])][3] = my_stoi(getDatas[j + 6]);
				j += 6;
				continue;
			}
		}
	}

	char str[10];
	printf("Enter a hex value:");
	gets(str);
	unsigned vaule = my_stoi(str);
	unsigned co = (vaule & 0b11);
	unsigned ci = ((vaule & (0b1111 << 2 ))>>2);
	unsigned vpo = (vaule & 0b111111);
	unsigned vpn = ((vaule& (0b11111111<<6 ))>>6);

	if (vpn <= 15){
		printf("The byte value is %02X\n",Cachearray[ci][Pagearray[vpn]][co]);
	}
	else{
		printf("It can not be determined\n");
	}
	return 0;
}
