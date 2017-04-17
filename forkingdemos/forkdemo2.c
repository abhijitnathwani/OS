#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    int pid;
    char c = 'a';	

    c = getchar();
    while(c != 'z'){
	printf("Parent ID: %d\n",getpid());
	if( (pid = fork()) == -1){
		perror("Fork:");
		_exit(-1);
	} 
	if(pid == 0) {
		printf("Child ID: %d of parent: %d \n",getpid(),getppid());
		printf("%c%c%c%c%c\n", c,c,c,c,c);
		_exit(0);
	} else c = getchar();
    }	
    return 0;
}
