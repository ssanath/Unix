#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main(int argc, char * argv[])
{
	int pid = fork();
	
	if(pid<0)
	{
		perror("fork");
	}
	else if(pid == 0)
	{
		execl("./program","program",argv[1],argv[2],(char *)NULL);
		perror("execl failed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		waitpid(pid,&status,0);
		if(WIFEXITED(status))
		{
			printf("Child process exited with status: %d\n", WEXITSTATUS(status));
		}
		else
		{
			printf("Child terminated abnormally");
		}
	}
	
	return 0;
}
