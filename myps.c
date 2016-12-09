#include "myHeader.h"

#define MAX 1024
typedef struct procsess
{
    int uid;
    int pid;
    int ppid;
    time_t stime;
	char cmd[MAX];
} proc_st;

void getCmdline(char *, char []);
void getStatinfo(char *, char *, char *, char *);

void myps(char *commandSet[]){
	DIR *dp;	//디렉터리 정보를 갖는 구조체 변수
    struct dirent *dirp; // 디렉터리 내용물의 정보를 갖는 구조체 변수
    struct stat buf;	// 파일의 정보를 저장하기 위한 구조체 변수
    char file_path[MAX]; // 프로세스 정보에 접근하기 위한 경로를 저장한 배열
	char *p_status = NULL, *ppid_buf = NULL, *time_buf=NULL; // 프로세스 상태정보를 저장하기 위한 포인터 변수
    FILE *fp;
    proc_st temp; // 프로세스 정보를 저장하기 위한 구조체 변수
	
	if(commandSet[1] == 0)
	{
		if((dp = opendir("/proc")) < 0)
		{
			fprintf(stderr, "direcrtoy error!\n");
			exit(1);
		}
		printf("<UID>\t<PID>\t<PPId>\t<STIME>\t<CMD>\n");
		while((dirp = readdir(dp)) != NULL)
		{
			memset(file_path, 0, sizeof(file_path));
			lstat(dirp->d_name, &buf);
			if(!S_ISDIR(buf.st_mode))
				continue;
			temp.uid = buf.st_uid; // uid
			temp.pid = atoi(dirp->d_name); //pid
			if(temp.pid != 0) // pid = 0 -> scheduler
			{
				sprintf(file_path, "/proc/%d/cmdline", temp.pid);
				getCmdline(file_path, temp.cmd);
		
				sprintf(file_path, "/proc/%d/stat", temp.pid); //status, ppid, time
//				getStatinfo(file_path, p_status, ppid_buf, time_buf);
//				temp.ppid = atoi(ppid_buf);
				printf("%d \t %d \t %d \t %s\n", temp.uid, temp.pid, temp.ppid, temp.cmd); // 출력
			}
		}
	    closedir(dp);
	}
	else if(strcmp(commandSet[1], "--help") == 0) // 사용법 출력
	{
		fprintf(stdout, "Usage : myps\n\n");
		fprintf(stdout, " - print process list\n\n");
	}
	else
	{
		fprintf(stderr, "ERROR : myps error ocurred\n");
	}
}

void getCmdline(char *file, char buf[])
{
	int fd;
	
	fd = open(file, O_RDONLY);

	memset(buf, 0x00, MAX);
	read(fd, buf, MAX);
	close(fd);
}

void getStatinfo(char *file, char *p_status, char *ppid, char *time_buf)
{
	int fd, i;
	char buf[MAX] = {0,};
	char *temp_token = NULL;
	
	fd = open(file, O_RDONLY);
	read(fd, buf, MAX);
	close(fd);
	temp_token = strtok(buf, " ");
	for(i=0;i<21;i++)
	{
		temp_token = strtok(NULL, " ");
		if(i == 1)
			p_status = temp_token;
		if(i == 2)
			ppid = temp_token;
		if(i == 20)
			time_buf = temp_token;
	}
}
