
/**
* @brief Creates the fan of process by passing a number through command line argument
*
* @param argc
* @param argv[]
*
* @return 0
*/
#include <stdio.h>
#include <unistd.h>
	
int main(int argc, char *argv[]){
	int pid, npid;
	int status;
	int a = atoi(argv[1]);
	printf("Parent id = %d\n",getpid());
	
	while(a != 0){
		if( (pid = fork()) == -1){
			perror("Fork:");
			_exit(-1);
		}
	 
		if(pid == 0) {
			printf("I am child, pid = %d, parent = %d, fork() returned %d  A = %d\n\n",getpid(), getppid(), pid,a);
			if(a>0)
			a--;
			else
			_exit(0);
		} else {
			printf("I am parent, pid = %d, fork() returned %d\n", getpid(), pid);

			npid = wait(&status);
			printf("child %d died with status code = %d\n", npid, status);
			getchar();
			_exit(0);	
		}	
	}
//	getchar();
	return 0;
}
