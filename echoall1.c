#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[], char *env[])
{
	printf("Arguments:\n");
	for(int i=0;i<argc;i++)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}
	
	for(char **envp=env;*envp!=NULL;envp++)
	{
		printf("%s\n", *envp);
	}
	return 0;
}
