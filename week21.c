#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	char buf[50];
	int n,fd1=0,fd2=0;
	if((fd1=open("hello.txt",O_RDWR,0))<0)
	{
		printf("Read error");
	}
	fd2 = dup(fd1);
	printf("%d %d",fd1,fd2);
	n = read(fd1,buf,10);
	lseek(fd2,0L,SEEK_END);
	write(fd2,buf,n);
	printf("%s\n",buf);
	
	return 0;
}
