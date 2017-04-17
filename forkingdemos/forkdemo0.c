#include<stdio.h>
#include<unistd.h>
int main()
{
	int pid;
	pid=fork();
	if(pid!=0)
//{
		printf("Current process id is %d \n Child process id is %d\n parent process id is %d \n",getpid(),pid,getppid());
//}
	getchar();
	return 0;
}
