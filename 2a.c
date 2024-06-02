#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
	struct stat fileStat;
	if(argc<2)
	{
		fprintf(stderr,"Invalid number of arguments\n");
		exit(1);
	}
	if(stat(argv[1],&fileStat)<0)
	{
		return 1;
	}
	printf("Information of the file:\n");
	printf("Size of the file: %d bytes\n", fileStat.st_size);
	printf("No. of links: %d\n", fileStat.st_nlink);
	printf("No. of inodes: %d\n", fileStat.st_ino);
	printf("File permissions:\n");
	printf((S_ISDIR(fileStat.st_mode))?"d\n":"-\n");
	printf((fileStat.st_mode & S_IRUSR)?"r\n":"-\n");
	printf((fileStat.st_mode & S_IWUSR)?"w\n":"-\n");
	printf((fileStat.st_mode & S_IXUSR)?"x\n":"-\n");
	printf((fileStat.st_mode & S_IRGRP)?"r\n":"-\n");
	printf((fileStat.st_mode & S_IWGRP)?"w\n":"-\n");
	printf((fileStat.st_mode & S_IXGRP)?"x\n":"-\n");
	printf((fileStat.st_mode & S_IROTH)?"r\n":"-\n");
	printf((fileStat.st_mode & S_IWOTH)?"w\n":"-\n");
	printf((fileStat.st_mode & S_IXOTH)?"x\n":"-\n");
	printf("The file %s a symbolic link\n",(S_ISLNK(fileStat.st_mode))?"is":"is not");
	return 0;
}
