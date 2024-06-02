#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd=0,n=0;
	char buff[20];
	if((fd=open("test.txt",O_RDONLY))<0)
	{
		printf("Could not open the file\n");
		exit(1);
	}
	if(read(fd,buff,20) != 20)
	{
		printf("File read operation failed\n");
	}
	else
	{
		write(STDOUT_FILENO,buff,20);
	}
	printf("\n");
	if(lseek(fd,10,SEEK_SET)<0)
	{
		printf("Seek operation failed\n");
	}
	if(read(fd,buff,20) != 20)
	{
		printf("File read operation failed\n");
	}
	else
	{
		write(STDOUT_FILENO,buff,20);
	}
	printf("\n");
	if(lseek(fd,10,SEEK_CUR)<0)
	{
		printf("Seek operation failed\n");
	}
	if(read(fd,buff,20) != 20)
	{
		printf("File read operation failed\n");
	}
	else
	{
		write(STDOUT_FILENO,buff,20);
	}
	printf("\n");
	if((n=lseek(fd,0,SEEK_END))<0)
	{
		printf("Seek operation failed\n");
	}
	printf("Size of the file is %d bytes\n", n);
	
	return 0;
}
