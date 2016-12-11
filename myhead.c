#include "myHeader.h"

#define MAX 128

void myhead(char *commandSet[])
{
	char buffer[MAX] = {0,};
	FILE *fp; // 파일 포인터 변수
	int i=0; // 반복문을 위한 변수

	if(commandSet[1] == 0) // 파일 이름이 입력안됬을 때 오류 출력
	{
		fprintf(stderr, "ERROR : myhead error ocurred\n");
	}
	else if(strcmp(commandSet[1], "--help") == 0) // 도움말 출력
	{
		fprintf(stdout, "Usage : myhead [FILENAME]\n\n");
		fprintf(stdout, "[FILENAME]		- print 5 lines of file content\n");
		fprintf(stdout, "[FILENAME][NUMBER]	- print n lines of file content\n\n");
	}
	else
	{
		if((fp = fopen(commandSet[1], "r")) == 0) // file open
		{
			fprintf(stderr, "ERROR : myhead error(file open error) ocurred\n");
		}
		else
		{
			if(commandSet[2] == 0) // 파일내용중 5라인 출력
			{
				while(i<5)
				{
					fgets(buffer, MAX, fp);
					fputs(buffer, stdout);
					i++;
				}
			}
			else if(isdigit(atoi(commandSet[2]) == 0))
			{
				fprintf(stderr, "ERROR : myhead error ocurred\n");
			}
			else // print n lines file contect
			{
				while(i<atoi(commandSet[2]))
				{
					if(fgets(buffer, MAX, fp)) // 파일 전체라인수가 n lines보다 클때
						fputs(buffer, stdout);
					else				 // 파일 전체 라인수가 n lines보다 작을때
						break;
					i++;
				}
			}
			fflush(fp);	
		}

		fclose(fp); // file close
	}	

}
