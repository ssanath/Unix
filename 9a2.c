#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main()
{
	struct stat statbuf;
	
	if(stat("foo.txt",&statbuf)<0)
	{
		fprintf(stderr,"stat error for foo.txt\n");
	}
	if(chmod("foo.txt",(statbuf.st_mode & ~S_IXGRP) | S_ISGID)<0)
	{
		fprintf(stderr,"chmod error for foo.txt\n");
	}
	if(chmod("bar.txt",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0)
	{
		fprintf(stderr,"chmod error for bar.txt\n");
	}
	
	return 0;
}
