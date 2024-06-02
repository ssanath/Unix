#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc, char* argv[])
{
	int fd1,fd2,n,size;
	char buffer[100];
	
	if(argc != 3)
	{
		fprintf(stderr,"Invalid number of parameters\n");
	}
	
	fd1 = open(argv[1],O_RDONLY,0666);
	if(fd1 == -1)
	{
		fprintf(stderr,"Coud not open the input file\n");
		exit(1);
	}
	
	fd2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(fd2 == -1)
	{
		fprintf(stderr,"Coud not open the output file\n");
		exit(1);
	}
	
	size = lseek(fd1,0L,SEEK_END);
	if(size == -1)
	{
		fprintf(stderr,"lseek\n");
		exit(1);
	}
	
	lseek(fd1,0L,SEEK_SET);
	
	n = read(fd1,buffer,size);
	if(n == -1)
	{
		fprintf(stderr,"Coud not read the input file\n");
		exit(1);
	}
	
	n = write(fd2,buffer,size);
	if(n != size)
	{
		fprintf(stderr,"Error writing into the output file\n");
		exit(1);
	}
	else
	{
		printf("File copied successfully!\n");
	}
	
	return 0;
}
