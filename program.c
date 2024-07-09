#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char * argv[])
{
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);
	printf("The sum is %d\n", num1+num2);
	return 0;
}
