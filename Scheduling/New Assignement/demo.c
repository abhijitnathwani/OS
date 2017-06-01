#include <stdio.h>
#include <unistd.h>

int pid1,pid2,pid3,pid4;

int main()
{
	if(((pid1=fork()) && (pid2=fork()) && (pid3=fork()) && (pid4=fork())) == 0)
	{
		printf("I am child with PID: %d and PPID: %d \n",getpid(),getppid());
if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
	{
		printf("Could not set CPU Affinity \n");
	}
//		printf("PID1: %d\tPID 2: %d\tPID 3: %d\tPID 4: %d\t\n",pid1,pid2,pid3,pid4);
	}
	while(1);
}
