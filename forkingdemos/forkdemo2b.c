#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	int pid, npid;
	int status;
	
	if( (pid = fork()) == -1){
		perror("Fork:");
		_exit(-1);
	} 
	if(pid == 0) {
		printf("I am child, pid = %d, parent = %d, fork() returned %d\n", 
				getpid(), getppid(), pid);
	} else {
		printf("I am parent, pid = %d, fork() returned %d\n", getpid(), pid);
//		while(1);

		getchar();
		npid = wait(&status);
		printf("child %d died with status code = %d\n", npid, status);
	}
	return 0;
}
