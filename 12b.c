#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	char *env[] = {"USER=child","PATH=/custom/path","HOME=/home/child",NULL};
	pid = fork();
	if(pid<0)
	{
		perror("fork error\n");
		exit(1);
	}
	else if(pid==0)
	{
		execle("./print_env","print_env",NULL,env);
		perror("execle error\n");
		exit(1);
	}
	else
	{
		wait(NULL);
		execlp("./print_env","print_env",NULL);
	}
	return 0;
}
