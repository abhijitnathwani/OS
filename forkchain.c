#include <stdio.h>
#include <unistd.h>
int main()
{
   int pid1,pid2,pid3,pid4,pid5;
   pid1=fork();
	if(pid1==0)
	{
		pid2=fork();
	}
	if(pid2==0)
	{
		pid3=fork();
	}
	if(pid3==0)
	{
		pid4=fork();
	}
	
	if(pid1>0 && pid2==0  && pid3>0)
{
fork();
}
	


   printf("forked\n");
   while(1);
   return 0;
}
