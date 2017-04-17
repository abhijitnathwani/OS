#include <stdio.h>
#include <unistd.h>
int main()
{
   int pid0,pid1,pid2,pid3,pid4,pid5,pid6,pid7,pid8,pid9,pid10,pid11,pid12;
   pid0=fork();
	if(pid0==0)
	{
		pid1=fork();
	}
	if(pid1==0)
	{
		pid3=fork();
	}
	if(pid0>0)
	{
		pid2=fork();
	}
	
	
	
	
	


   printf("forked\n");
   while(1);
   return 0;
}
