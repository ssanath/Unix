#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

void print_file_flags(int fd)
{
	int flags=0;
	if((flags = fcntl(fd,F_GETFL))<0)
	{
		fprintf(stderr,"flag error\n");
		exit(EXIT_FAILURE);
	}
	
	int accMode = flags & O_ACCMODE;
	
	if(accMode == O_RDONLY)
	{
		printf("Readonly\n");
	}
	else if(accMode == O_WRONLY)
	{
		printf("Writeonly\n");
	}
	else if(accMode == O_RDWR)
	{
		printf("Read/Write\n");
	}
	else
	{
		printf("Unknow acess mode\n");
	}
	
	//other flags
	
	if(flags & O_NONBLOCK)
	{
		printf("Non blocking\n");
	}
	if(flags & O_APPEND)
	{
		printf("Append\n");
	}
	if(flags & O_SYNC)
	{
		printf("Synchronous writes\n");
	}
	if (flags & O_DSYNC)
	{
        	printf("Synchronous data writes\n");
	}
	if (flags & O_RSYNC) {
		printf("Synchronous read operations\n");
	}
}

int main(int argc, char* argv[])
{
	int fd = 0;
	if((fd=open(argv[1],O_RDWR,0))<0)
	{
		fprintf(stderr,"Error opening the file\n");
	}
	printf("File descriptor: %d\n",fd);
	
	print_file_flags(fd);
	return 0;
}
