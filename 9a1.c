#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main()
{
	umask(0);
	if(creat("foo.txt",RWRWRW)<0)
	{
		printf("creat error for foo.txt");
	}
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	
	if(creat("bar.txt",RWRWRW)<0)
	{
		printf("creat error for bar.txt");
	}
	return 0;
}
