#include<stdio.h>
#include<unistd.h>
#define CHILD 5
int main()
{
	int pid;
	int i,status;
	printf("I am parent PID: %d \n",getpid());
	for(i=0;i<CHILD;i++)
	{
		
		if((pid=fork())==0)
		{
			printf("I am child with PID: %d, parent PID: %d\n",getpid(),getppid());
			_exit(0);
		}
	//	else
	//		printf("I am some process with PID: %d \n",getpid());
		
//		printf("I am child with PID: %d, parent PID: %d\n",pid,getppid());
	}
//	wait(&status);
//	getchar();
	while(1);
	return 0;	
}
