#include "myHeader.h"

void myenv(char *commandSet[])
{
	extern char **environ;
	int i=0;
	
	if(commandSet[1] == 0)	// 모든 환경변수 출력
	{	
		while(environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
	else if(strcmp(commandSet[1], "--help") == 0) // 도움말 출력
	{
		fprintf(stdout, "Usage : myenv [STRING]\n\n");
		fprintf(stdout, "[STRING]	- Print [STRING] environment variable\n");
		fprintf(stdout, "No [STRING]	- Pring all environment varable\n\n");
	}
	else // [STRING]이 입력될때 getenv()를 이용하여 [STRING]에 맞는 환경변수 출력
	{
		printf("%s=%s\n", commandSet[1], getenv(commandSet[1]));
	}
}
