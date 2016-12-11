#include "myHeader.h"

int delete_all_dir(char []);

void myrm(char *commandSet[])
{
	struct stat buf; // 파일의 정보를 저장하기 위한 구조체 변수
	DIR *dp; // 디렉터리의 정보를 갖고 있는 구조체 변수
	struct dirent *dirp; // 디렉터리 내용물의 정보를 갖고 있는 구조체 변수
	char *ptr; // 해당 디렉터리의 위치를 저장하는 포인터변수
	ptr = getcwd(NULL, 0);

	if(commandSet[1] == 0) // 파일 이름이 입력안됬을때 오류 출력
	{
		fprintf(stderr, "ERROR : Myrm error ocurred\n");
	}
	else if(strcmp(commandSet[1], "--help") == 0) // 도움말 출력
	{
		fprintf(stdout, "USAGE : myrm [FILENAME]\n\n");
		fprintf(stdout, "no option		 - erase [FILENAME]file\n");
		fprintf(stdout, "-rf [FILENAME]  - erase [FILENAME] recursively and forcingly\n\n");
	}
	else
	{
		if((dp = opendir(ptr)) == NULL)
		{
			fprintf(stderr, "ERROR : Opendir error ocurred\n");
		}
		while((dirp = readdir(dp)) != NULL)
		{
			lstat(dirp->d_name, &buf);
			if(strcmp(commandSet[1], "-rf") == 0)	// -rf 옵션
			{
				if(strcmp(dirp->d_name, commandSet[2]) == 0)
				{
					if(S_ISDIR(buf.st_mode))
						delete_all_dir(commandSet[2]);
					else // 해당 파일이 파일일 경우
						unlink(commandSet[2]); // unlink()함수를 통해 삭제한다
				}
			}
			else // 옵션이 없을때
			{
				if(strcmp(dirp->d_name, commandSet[1]) == 0)
				{
					if(S_ISDIR(buf.st_mode)) // 디렉터리
						fprintf(stderr, "ERROR : File is directory\n");
					else
						if(unlink(commandSet[1]) != 0)
							fprintf(stderr, "ERROR : myrm error ocurred\n");
				}
			}
		}
		closedir(dp);
	}
}

int delete_all_dir(char *pathname){
	struct stat buf;
	DIR *dp;
	struct dirent *dirp;
	char *ptr;
	
	chdir(pathname);
	ptr = getcwd(NULL, 0);
	
	if((dp = opendir(ptr)) == NULL){
		printf("opendir error\n");
		return -1;
	}
	while((dirp = readdir(dp)) != NULL) //디렉터리 정보를 읽는다
	{
		if(strcmp(dirp->d_name, ".") == 0 ||
			strcmp(dirp->d_name, "..") == 0)
				continue;
		lstat(dirp->d_name, &buf);
		
		if(S_ISDIR(buf.st_mode))	//디렉터리 일 경우 모든 재귀적 함수 호출
			if(delete_all_dir(dirp->d_name) != 0) // recursive call, erase files
				return -1;

	}
	if(closedir(dp) < 0){
		printf("can't close directory\n");
		return -1;
	}
	chdir("..");
	rmdir(pathname); // 디렉터리 삭제
	return 0;
}
