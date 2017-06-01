#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void funcInterrupt(int); // function prototype for interuppt signal (ctrl + c )
void funcAbort(int); // function prototype for abort signal ( `kill -6 <pid>`, 6 : Abort SIGNAL)

int iInterrupt; // to keep a count of the received interuppt signals
int iAbort; // to keep a count of the received abort

int main()
{
	signal(SIGINT, funcInterrupt); // binding the SIGINT signal with the funcInterrupt
	signal(SIGABRT, funcAbort); // binding the SIGABRT signal with the funcAbort

	printf("Hello....Welcome to the program to check the working of Abort and interuppt signals.\n");

	while(1);
	return 0;
}

/* Function definition for the funcInterrupt() */ 
void funcInterrupt(int signum)
{
	printf("Interrupt = %d\n",++iInterrupt );
	
	printf("Interrupt received %d time(s)\n",iInterrupt);
	if(iInterrupt==5)
		exit(1);
}

/* Function definition for the funcAbort() */
void funcAbort(int signum)
{
	printf("Abort = %d\n", ++iAbort);
	printf("Abort received %d time(s)\n",iInterrupt);
	
}
