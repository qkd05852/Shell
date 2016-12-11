#include "myHeader.h"

#define MAX 1024

int string_compare_function(const void *a, const void *b);

void mysort(char *commandSet[])
{
	FILE *fp;	// 파일을 열기 위한 파일포인터변수
	int i=0, size = 0; // 반복문,파일크기를 저장하기위한 변수
	char buffer[MAX][MAX]={0,}; // 파일의 내용을 저장하는 2차원 배열
	char *buf = NULL;
	char buff[MAX] = {0,}; //파일 내용을 저장하기 위한 배열과 포인터

	memset(buffer, 0x00, sizeof(char *)*MAX);

	if(commandSet[1] == 0) // 아무것도 입력하지 않으면 오류출력
		fprintf(stderr, "ERROR : mysort error ocurred\n");
	else if(strcmp(commandSet[1], "--help") == 0) // 사용법 출력
	{
		fprintf(stdout, "Usage : mysort [FILENAME]\n\n");
		fprintf(stdout, "[FILENAME]	- sort file content\n\n");
	}
	else
	{
		if((fp = fopen(commandSet[1], "r")) == 0) 
			fprintf(stderr, "ERROR : mysort error(file open error) ocurred\n");
		else
		{
			fseek(fp, 0, SEEK_SET);
			while((buf = fgets(buff, MAX, fp)) != NULL){ // 반복문을 통해 파일의 내용을 fgets()를 이용해 읽고,buffer[][]에 저장.
				buff[strlen(buff)-1] = '\0';
				strcpy(buffer[i], buff);
				i++;
			}
			size = i;
			i=0;
			qsort((void *)buffer, size, sizeof(buffer[0]), string_compare_function); //정렬

			for (i = 0; i < size; i++) // 출력
				printf("%s\n", buffer[i]);
		}
		fclose(fp); // 파일닫기
	}
}

int string_compare_function(const void *a, const void *b) { // 정렬기능
	return(strcmp( (char *)a, (char *)b) );
}
