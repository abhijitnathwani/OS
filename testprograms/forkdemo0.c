#include<stdio.h>
#include<unistd.h>
int main()
{
	int pid=7;
	pid=fork();
	printf("Current ProcessID: %d\tChild ProcessID: %d\tParent ProcessID: %d\n",getpid(),pid,getppid());
}
