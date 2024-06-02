#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<utime.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char* argv[])
{
	struct stat statbuf_1;
	struct stat statbuf_2;
	struct utimbuf times;
	if(stat(argv[1],&statbuf_1)<0)
	{
		fprintf(stderr,"Error\n");
	}
	if(stat(argv[2],&statbuf_2)<0)
	{
		fprintf(stderr,"Error\n");
	}
	printf("Before copying:\n");
	printf("Access time: %s\n Modification time: %s\n", ctime(&statbuf_1.st_atime), ctime(&statbuf_1.st_mtime));
	times.modtime = statbuf_2.st_mtime;
	times.actime = statbuf_2.st_atime;
	
	if(utime(argv[1],&times)<0)
	{
		fprintf(stderr,"Error copying time..\n");
	}
	if(stat(argv[1],&statbuf_1)<0)
	{
		fprintf(stderr,"Error\n");
	}
	printf("After copying:\n");
	printf("Access time: %s\n Modification time: %s\n", ctime(&statbuf_1.st_atime), ctime(&statbuf_1.st_mtime));
	
	return 0;
}
