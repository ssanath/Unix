#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#define BUFFSIZE 100

int main()
{
	int n;
	char buff[BUFFSIZE];
	while((n = read(STDIN_FILENO,buff,BUFFSIZE))>0)
	{
		if(write(STDOUT_FILENO,buff,n) != n)
		{
			printf("Write error");
		}
	}
	if(n<0)
	{
		printf("Read error");
	}
	exit(0);
}
