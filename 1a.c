#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char*argv[])
{
	char buff[20];
	int n=0,source=0,dest=0;
	if(argc != 3)
	{
		fprintf(stderr,"Incorrect number of arguments have been supplied\n");
	}
	if((source=open(argv[1],O_RDONLY))<0)
	{
		fprintf(stderr,"Cannot open the source file\n");
		exit(-1);
	}
	if((dest=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC))<0)
	{
		fprintf(stderr,"Cannot open the destination file\n");
		exit(-1);
	}
	n = lseek(source,(off_t)0,SEEK_END);
	printf("Size of the source file is %d bytes\n",n);
	for(int i=n-1;i>=0;i--)
	{
		lseek(source,(off_t)i,SEEK_SET);
		
		if((read(source,buff,1)) != 1)
		{
			printf("Read error");
			exit(1);
		}
		if((write(dest,buff,1)) != 1)
		{
			printf("Write error");
			exit(1);
		}
	}
	write(STDOUT_FILENO,"Done\n",5);
	close(source);
	close(dest);
	return 0;
}
