#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		perror("fork\n");
	}
	else if(pid==0)
	{
		for(int i=0;i<10;i++)
		{
			printf("I am child, pid: %d\n", getpid());
		}
	}
	else
	{
		printf("I am parent\n");
		while(1);
	}
	return 0;
}
