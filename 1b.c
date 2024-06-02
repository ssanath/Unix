#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#define FILE_NAME "shared_file.txt"
#define SHARED_MEM_SIZE sizeof(int)

int main()
{
	int *offset_ptr;
	char *write_buffer = "This is written by the parent process\n";
	int fd;
	char read_buffer[100];
	
	fd = open(FILE_NAME,O_RDWR | O_CREAT,0666);
	if(fd==-1)
	{
		fprintf(stderr,"Could not open the file\n");
		exit(1);
	}	
	int shm_fd = shm_open("offset_shm",O_RDWR | O_CREAT,0666);
	if(shm_fd==-1)
	{
		fprintf(stderr,"shm_open\n");
		exit(1);
	}
	ftruncate(shm_fd,SHARED_MEM_SIZE);
	offset_ptr = mmap(NULL,SHARED_MEM_SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
	if(offset_ptr == MAP_FAILED)
	{
		fprintf(stderr,"mmap\n");
		exit(1);
	}
	pid_t pid = fork();
	if(pid<0)
	{
		fprintf(stderr,"Fork error\n");
		exit(1);
	}
	else if(pid == 0)
	{
		printf("Child process has started\n");
		lseek(fd,*offset_ptr,SEEK_SET);
		int bytes_read = read(fd,read_buffer,sizeof(read_buffer));
		if(bytes_read>0)
		{
			read_buffer[bytes_read] = '\0';
			printf("Child process read %d bytes: %s\n", bytes_read, read_buffer);
		}
		else
		{
			fprintf(stderr,"Could not read\n");
		}
		*offset_ptr = lseek(fd,0,SEEK_CUR);
		printf("Child process has finished\n");
	}
	else
	{
		printf("Parent process has started\n");
		write(fd,write_buffer,strlen(write_buffer));
		*offset_ptr = lseek(fd,0,SEEK_CUR);
		printf("Parent process has finished\n");
	}
	munmap(offset_ptr,SHARED_MEM_SIZE);
	close(shm_fd);
	close(fd);
	
	return 0;
}
