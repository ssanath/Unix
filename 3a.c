#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

int my_system(char *command)
{
	if(command == NULL)
	{
		return -1;
	}
	pid_t pid = fork();
	if(pid<0)
	{
		return -1;
	}
	else if(pid == 0)
	{
		execl("/bin/sh","sh","-c",command,(char*)NULL);
		fprintf(stderr,"execl\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		if(waitpid(pid,&status,0) == -1)
		{
			return -1;
		}
		if(WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}
		else
		{
			return -1;
		}
	}
}

int main()
{
	int result=0;
	printf("Executing ls -l command\n");
	result = my_system("ls -l");
	if(result == -1)
	{
		fprintf(stderr,"my_system\n");
	}
	else
	{
		printf("ls -l exited with status %d\n", result);
	}
	return 0;
}
