#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
	int fd,n;
	struct dirent *dir;
	DIR* dp;
	
	dp = opendir(".");
	
	if(dp)
	{
		while((dir=readdir(dp)) != NULL)
		{
			fd = open(dir->d_name,O_RDWR,0777);
			n= lseek(fd,0,SEEK_END);
			
			if(!n)
			{
				unlink(dir->d_name);
			}
		}
	}
	
	return 0;
}
