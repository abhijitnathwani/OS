#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<string.h>

main()
{ 
	int pipefd[2], n;
	char buff[100]="hello World",buff1[100];
	if (pipe(pipefd) < 0 ) 
		perror("pipe error");
	printf("read fd = %d, write fd = %d\n", pipefd[0], pipefd[1]);
	if (write(pipefd[1], buff, 12) != 12) 
		perror("write error");
	if ( (n=read(pipefd[0], buff1, sizeof(buff))) <=0) 
		perror("read error");
	write(1, buff, n); /*fd=1=stdout*/
} 
