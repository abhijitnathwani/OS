#include<stdio.h>
#include<unistd.h>
int main()
{
	int fd[2];
	int pid,status;
	char string[]="hello",string1[6];

	pipe(fd);
	if(pid=fork()==0)
	{
		dup2(fd[1],1);
		write(fd[1],string,6);
		_exit(0);
	}
	else
	{
	//wait(&status);
		dup2(fd[0],0);
		//wait(&status);
		read(fd[0],string1,6);
		printf("string1 = %s \n",string1);
	}
	return 0;
}

