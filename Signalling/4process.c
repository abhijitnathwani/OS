#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void funInterrupt(int);
long i = 400000000;
int j,iFlag;
int iPID = -1 ;
int main()
{

	signal(SIGINT, funInterrupt);

	printf("Welcome\n");

	while(1);
	{
		printf("parent %d count = %d\n",getpid(),j++);
		while(i >= 0)
			i--;
		// if(iPID > 0)
		// {
		// 	// iFlag=0;
		// 	kill(getpid(),SIGKILL);

		// }
		 i = 400000000;
	}
	return 0;
}


void funInterrupt(signum)
{
	
	printf("Interrupt received \n");
	iPID = fork();
	if(iPID == 0){
		printf("I am child %d of Parent %d\n",getpid(), getppid() );
		kill(getppid(),15);

		// while(1)
		// {
			// printf("count = %d\n",j++ );
			// while(i >= 0)
			// 	i--;
			// break;
			// 	i = 400000000;
		// }
		
	}
	// else{
	// exit(0);
	// // 	kill(getpid(),SIGKILL);
	//  }
	// // iFlag=1;

}
