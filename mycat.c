#include "myHeader.h"

void mycat(char *commandSet[])
{
	char ch = NULL; // 파일 내용을 읽고 저장하기 위한 변수
	int fd=0, i=0; // 파일 디스크립터를 저장하기위한 변수, 반복문을 위한 변수

	if(commandSet[1] == 0) // 파일이름이 없을때 오류 출력
	{
		fprintf(stderr, "ERROR : mycat error ocurred\n");
		exit(1);
	}
	else if(strcmp(commandSet[1], "--help") == 0) // 도움말 출력
	{
		fprintf(stdout, "Usage : mycat [FILENAME]\n\n");
		fprintf(stdout, "[FILENAME]		- print whole file content\n");
		fprintf(stdout, "[FILENAME][NUMBER]	- print n byte file content\n");
		fprintf(stdout, "			- if n byte is bigger than file size, print while file content\n\n");
	}
	else
	{
		if((fd = open(commandSet[1], O_RDONLY)) == 0) // file open
		{
			fprintf(stderr, "ERROR : mycat error(file open error) ocurred\n");
		}
		else
		{
			if(commandSet[2] == 0) // 파일의 전체내용을 출력
			{
				while(read(fd, &ch, 1))
					write(1, &ch, 1);
			}
			else if(isdigit(atoi(commandSet[2]) == 0))
			{
				fprintf(stderr, "ERROR : mycat error ocurred\n");
			}
			else // print n byte file contect
			{
				for(i=0;i<atoi(commandSet[2]);i++)
				{
					if(read(fd, &ch, 1)) // 파일크기가 > n byte보다 클 때
						write(1, &ch, 1);
					else				 // 파일크기가 < n byte보다 작을 때
						break;
				}
				printf("\n");
			}
			
		}
		close(fd); // file close
	}	

}
