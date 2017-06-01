/*Explore by setting different values for num_CPUs values and CPU_SET*/
/*          You can see effect from /proc/<pid>/status               */ 
/*             Try to run threads on multiple CPUs                   */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>

int funcFactorial(int,int);


int pid1,pid2,pid3,pid4,count=10;


int main(void) 
{

	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int iret1, iret2;

	//Setting CPU affinity
	
	cpu_set_t mask1,mask2,mask3,mask4;

	/* CPU_ZERO initializes all the bits in the mask to zero. */
	CPU_ZERO(&mask1);
	CPU_ZERO(&mask2);
	CPU_ZERO(&mask3);
	CPU_ZERO(&mask4);

	/* CPU_SET sets only the bit corresponding to cpu. */
	CPU_SET(0, &mask1);
	CPU_SET(0, &mask2);
	CPU_SET(0, &mask3);
	CPU_SET(0, &mask4);



	if(((pid1=fork()) && (pid2=fork()) && (pid3=fork()) && (pid4=fork())) == 0)
	{
		///printf("I am child with PID: %d and PPID: %d \n",getpid(),getppid());
		if(pid1==0)
	{
		if (sched_setaffinity(0, sizeof(mask1), &mask1) == -1)
		{
			printf("Could not set CPU Affinity \n");
		}
		setpriority(PRIO_PROCESS,0,-9);
		//printf("Priority: 111\tFactorial from PID: %d is %d\n",getpid(),funcFactorial(10,getpid()));/
		funcFactorial(1,getpid());
	}
	else if(pid2==0)
	{
		if (sched_setaffinity(0, sizeof(mask2), &mask2) == -1)
		{
			printf("Could not set CPU Affinity \n");
		}
		setpriority(PRIO_PROCESS,0,3);
//		printf("Priority: 123\tFactorial from PID: %d is %d\n",getpid(),funcFactorial(10));
		funcFactorial(10,getpid());
	}
	else if(pid3==0)
	{
		if (sched_setaffinity(0, sizeof(mask3), &mask3) == -1)
		{
			printf("Could not set CPU Affinity \n");
		}
		setpriority(PRIO_PROCESS,0,10);
//		printf("Priority: 130\tFactorial from PID: %d is %d\n",getpid(),funcFactorial(10));
		funcFactorial(10,getpid());
	}	
	else if(pid4==0)
	{
		if (sched_setaffinity(0, sizeof(mask4), &mask4) == -1)
		{
			printf("Could not set CPU Affinity \n");
		}
		setpriority(PRIO_PROCESS,0,19);
//		printf("Priority: 139\tFactorial from PID: %d is %d\n",getpid(),funcFactorial(10));
		funcFactorial(10,getpid());
	}
		

	}


	while(1);
	return 0;
}
int funcFactorial(int n,int pid)
{
   printf("Count : %d PID: %d\n",++count,pid);

   /* if (n >= 1)
        return n*funcFactorial(n-1);
    else
        return 1;*/
   return 0;
}
