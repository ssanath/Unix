#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<string.h>
#define SHARED_FILE "share.txt"
#define SHARED_MEM_SIZE sizeof(int)
int main(int argc, char* argv[])
{
	int *offset_ptr;
	int fd;
	char buf[100];
	char *write_buf = "This is written by the parent";
	
	fd = open(SHARED_FILE,O_RDWR|O_CREAT,0666);
	int shm_fd = shm_open("offset_shm",O_RDWR|O_CREAT,0666);
	ftruncate(shm_fd,SHARED_MEM_SIZE);
	offset_ptr = mmap(NULL,SHARED_MEM_SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("Child\n");
		 sleep(1);
		lseek(fd,*offset_ptr,SEEK_SET);
		int size = read(fd,buf,sizeof(buf));
		buf[size] = '\0';
		printf("Child process read %d bytes: %s\n", size,buf);
		*offset_ptr = lseek(fd,0,SEEK_CUR);
	}
	else
	{
		printf("Parent\n");
		write(fd,write_buf,strlen(write_buf));
		*offset_ptr = lseek(fd,0,SEEK_CUR);
		wait(NULL);
	}
	munmap(offset_ptr,SHARED_MEM_SIZE);
	close(shm_fd);
	close(fd);	
	return 0;
}
