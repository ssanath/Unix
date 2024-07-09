#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
	int fd1,fd2;
	char buf[10] = "Hi!!";
	fd1 = open("hello.txt",O_RDWR,0);
	if(fd1<0)
	{
		fprintf(stderr,"Error\n");
	}
	fd2 = dup(fd1);
	printf("fd1: %d, fd2: %d\n", fd1, fd2);
	lseek(fd2,0L,SEEK_END);
	write(fd2,buf,4);
	return 0;
}
