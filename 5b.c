#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/stat.h>
#include<sys/types.h>

void sigint_handler(int signum)
{
	printf("Caught SIGINT: %d\n", signum);
	
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags=0;
	sigemptyset(&sa.sa_mask);
	
	if(sigaction(SIGINT,&sa,NULL) == -1)
	{
		fprintf(stderr,"Sigaction\n");
		exit(EXIT_FAILURE);
	}
}

int main()
{
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sa.sa_flags=0;
	sigemptyset(&sa.sa_mask);
	
	if(sigaction(SIGINT,&sa,NULL) == -1)
	{
		fprintf(stderr,"sigaction\n");
		exit(EXIT_FAILURE);
	}
	printf("Press Ctrl+C, for default handler press Ctrl+C again\n");
	
	while(1)
	{
		pause();
	}
	
	return 0;
}
