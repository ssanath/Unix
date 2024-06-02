#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	int status;
	
	pid = fork();
	
	if(pid == 0)
	{
		printf("Child process is executing\n");
		
		char* args[] = {"./interpreter","arg1","arg2",NULL};
		char* env[] = {"VAR1=value1","VAR2=value2",NULL};
		
		execve(args[0],args,env);
		fprintf(stderr,"execve\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid,&status,0);
	
		printf("Parent process is executing\n");
		
		char* args[] = {"./interpreter","arg3","arg4",NULL};
		
		execvp(args[0],args);
		fprintf(stderr,"execvp\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
