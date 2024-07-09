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
		printf("First child:%d\n", getpid());
		if((pid=fork())<0)
		{
			perror("fork\n");
		}
		else if(pid>0)
		{
			exit(0);
		}
		sleep(2);
		printf("Second child's parent pid=%ld\n", (long)getppid());
		exit(0);
	}
	if(waitpid(pid,NULL,0) != pid)
	{
		perror("waitpid error\n");
	}
	return 0;
}
