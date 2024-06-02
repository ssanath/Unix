#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

int main()
{
	int status;
	pid_t parent_pid = getpid();
	
	pid_t pid = fork();
	
	if(pid<0)
	{
		fprintf(stderr,"fork\n");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		pid_t child_pid = getpid();
		
		printf("Child process of pid %d is executing...\n", child_pid);
		
		if((access("hello.txt",F_OK))==0)
		{
			printf("File can be accessed\n");
		}
		else
		{
			printf("File cannot be accessed\n");
		}
		
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Parent process of pid %d is executing...\n", parent_pid);
		
		waitpid(pid,&status,0);
		
		printf("Parent process: child process %d has exited\n", pid);
	}
	return 0;
}
