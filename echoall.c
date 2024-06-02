#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[], char* env[])
{
	printf("Received arguments:\n");
	for(int i=0;i<argc;i++)
	{
		printf("arg[%d]: %s\n",i,argv[i]);
	}
	
	printf("Received environment variables:\n");
	for(char** envp=env;*envp != NULL;envp++)
	{
		printf("%s\n", *envp);
	}
	
	return 0;
}
