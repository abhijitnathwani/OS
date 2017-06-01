#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void funcInterrupt(int); // function prototype for interuppt signal (ctrl + c )
void funcAbort(int); // function prototype for abort signal ( `kill -6 <pid>`, 6 : Abort SIGNAL)

int iCount; // global variable to keep a track of count variable
int iAbort; // to keep a count of the received abort
int iPID; // to get the pid of the forked process
int iPPID; // to get the pid of the parent process
int main()
{
	signal(SIGINT, funcInterrupt); // binding the SIGINT signal with the funcInterrupt
	signal(SIGABRT, funcAbort); // binding the SIGABRT signal with the funcAbort

	printf("Welcome\n");	

	

	while(1);
	
	return 0;
}

/* Function definition for the funcInterrupt() */ 
void funcInterrupt(int signum)
{


	iPID = fork();
	if(iPID != 0)
	{
		iPPID=getppid();
		printf("CHILD Process created\n");
		
	}
}
/* Function definition for the funcAbort() */
void funcAbort(int signum)
{
	printf("PID: %d\tPPID: %d",getpid(),getppid());
	printf("Abort Signal received\n");
	printf("=====================\n");
	printf("Exiting Parent and Child Process....\n");
	//kill(iPID,SIGKILL);
	kill(iPPID,SIGKILL);
	
}
