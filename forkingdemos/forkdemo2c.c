#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	int pid;
	
	if( (pid = fork()) == -1){
		perror("Fork:");
		_exit(-1);
	} 
	if(pid == 0) {
		printf("I am child, pid = %d, parent = %d, fork() returned %d\n", 
				getpid(), getppid(), pid);
		while(1) sleep(1);
	} else {
		printf("I am parent, pid = %d, fork() returned %d\n", getpid(), pid);
		while(1) sleep(1);
	}
	return 0;
}
