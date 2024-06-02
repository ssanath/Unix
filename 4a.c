#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char* argv[])
{
	if(argc == 3)
	{
		printf("Hard linking %s %s\n", argv[1], argv[2]);
		if(link(argv[1],argv[2]) == 0)
		{
			printf("Hard link created\n");
		}
		else
		{
			printf("Hard link could not be created\n");
		}
	}
	else if(argc == 4)
	{
		printf("Soft linking %s %s\n", argv[1], argv[2]);
		if(symlink(argv[1],argv[2]) == 0)
		{
			printf("Soft link created\n");
		}
		else
		{
			printf("Soft link could not be created\n");
		}
	}
	else
	{
		printf("Invalid number of parameters\n");
	}
	return 0;
}
