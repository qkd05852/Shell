#include "myHeader.h"

#define MAX 128

void mytail(char *commandSet[])
{
	char buffer[MAX] = {0,};
	FILE *fp; //파일 포인터 변수
	int i=0, last_line_count=0; // 반복문을 위한 변수, 마지막줄부터 라인 수를 세기 위한 변수

	if(commandSet[1] == 0) // 파일이름이 입력되지 않았을때 오류 출력
	{
		fprintf(stderr, "ERROR : mytail error ocurred\n");
	}
	else if(strcmp(commandSet[1], "--help") == 0) // 도움말 출력
	{
		fprintf(stdout, "Usage : mytail [FILENAME]\n\n");
		fprintf(stdout, "[FILENAME]		- print last 5 lines of file content\n");
		fprintf(stdout, "[FILENAME][NUMBER]	- print last n lines of file content\n\n");
	}
	else
	{
		if((fp = fopen(commandSet[1], "r")) == 0) // file open
		{
			fprintf(stderr, "ERROR : mytail error(file open error) ocurred\n");
		}
		else
		{
			fseek(fp, 0, SEEK_END);
			if(commandSet[2] == 0) // 파일 내용중 마지막 5라인 출력
			{
				while(ftell(fp) != 0) // 파일 포인터를 끝으로 옮겨 파일내용의 마지막5라인 출력
				{
					fseek(fp, -2, SEEK_CUR);
					if(fgetc(fp) == '\n') // '\n'의 라인수를 셈
						last_line_count++; // 마지막 5줄의 시작포인터를 찾아냄
					if(last_line_count == 5) 
						break;
				}
				while(i<5) // 파일내용의 마지막 5라인 출력
				{
					fgets(buffer, MAX, fp);
					fputs(buffer, stdout);
					i++;
				}
			}
			else if(isdigit(atoi(commandSet[2]) == 0))
				fprintf(stderr, "ERROR : mytail error ocurred\n");
			else // 파일내용의 마지막 n라인 출력
			{
				while(ftell(fp) != 0) // 파일 포인터를 옮겨 파일내용의 마지막n라인 출력
				{
					fseek(fp, -2, SEEK_CUR);
					if(fgetc(fp) == '\n') // '\n'의 라인수를 셈
						last_line_count++;
					if(last_line_count == atoi(commandSet[2]))
						break;
				}
				while(i<atoi(commandSet[2])) // 파일 내용의 마지막 n라인 출력
				{
					fgets(buffer, MAX, fp);
					fputs(buffer, stdout);
					i++;
				}
			}	
		}
		fclose(fp); // 파일 닫음
	}	

}
