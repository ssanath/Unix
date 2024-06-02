#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<time.h>

int main(int argc, char* argv[])
{
	struct stat mystat;
	struct dirent *dir;
	DIR *dp;
	dp = opendir(".");
	
	if(dp)
	{
		while(dir=readdir(dp))
		{
			stat(dir->d_name,&mystat);
			printf("%d %d %d %d %s %s\n",mystat.st_ino,mystat.st_mode,mystat.st_uid,mystat.st_gid,ctime(&mystat.st_atime),dir->d_name);
		}
	}
}
