#include <stdio.h>
#include <unistd.h>
int main()
{
   int pid1,pid2,pid3;
   pid1=fork();
	if(pid1==0)
	{
		pid2=fork();
	}
	fork();

   printf("forked\n");
   while(1);
   return 0;
}
