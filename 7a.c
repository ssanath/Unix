#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>

static int globval;
static jmp_buf jmpbuffer;

static void f1(int,int,int,int);
static void f2(void);

int main()
{
	int autoval;
	register int regival;
	volatile int volval;
	static int statval;
	
	globval=1;autoval=2;regival=3;volval=4;statval=5;
	
	if(setjmp(jmpbuffer) != 0)
	{
		printf("After longjmp:\n");
		printf("globval=%d,autoval=%d,regival=%d,volval=%d,statval=%d\n",globval,autoval,regival,volval,statval);
	}
	else
	{
		globval=97;autoval=98;regival=99;volval=100;statval=101;
		f1(autoval,regival,volval,statval);
	}
	
	return 0;
}

static void f1(int i,int j,int k,int l)
{
	printf("In f1()\n");
	printf("globval=%d,autoval=%d,regival=%d,volval=%d,statval=%d\n",globval,i,j,k,l);
	globval = 1000;
	j = 1000;
	f2();
}

static void f2()
{
	longjmp(jmpbuffer,1);
}
