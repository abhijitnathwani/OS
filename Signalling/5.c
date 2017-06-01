#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int iAbortCount;	//for counting number of abort singnal
void funcAbort(int);	// function prototype for abort signal ( `kill -6 <pid>`, 6 : Abort SIGNAL)

int main()
{
	signal(SIGABRT,funcAbort); // binding the SIGABRT signal with the funcAbort
	printf("Value of SIGABRT %d\n",SIGABRT);

	while(1); // running the code infinitely.
	return 0;
}

void funcAbort(int signum)
{
	printf("Abort count = %d\n",++iAbortCount );	// print the count of abort signal.	

	printf("Abort Signal received %d time(s)\n",iAbortCount);

	if(iAbortCount==5)		//condition for termination of program
	{
		printf("Abort Signal received 5 times.\n");
		printf("Exiting the program now.......\n");
		exit(0);
	}
}
