#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void funcInterrupt(int); // function prototype for interuppt signal (ctrl + c )

int iCount; // global variable to keep a track of count variable
long iDelay=400000000,iDelay2;
int main()
{
	signal(SIGINT, funcInterrupt); // binding the SIGINT signal with the funcInterrupt
	printf("Welcome\n");	

	

	do
	{
		printf("Count Parent: %d\n",++iCount);
		while(iDelay>0)
			iDelay--;
		iDelay2++;
		iDelay=400000000;
	}while(iDelay2>0);
	return 0;
}

/* Function definition for the funcInterrupt() */ 
void funcInterrupt(int signum)
{
	int iPID; // to get the pid of the forked process
	printf("Function called\n");
	iPID = fork();
	if(iPID == 0)
	{
		kill(getppid(),SIGKILL);
		signal(SIGINT, funcInterrupt); // binding the SIGINT signal with the funcInterrupt
		printf("Printed in CHILD\n");
		do
		{
			printf("Count in Child: %d,PID: %d\n",++iCount,getpid());
			while(iDelay>0)
				iDelay--;
			iDelay2++;
			iDelay=400000000;
		}while(iDelay2>0);
	}
}
