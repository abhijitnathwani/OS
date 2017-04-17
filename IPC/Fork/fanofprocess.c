/**
* @brief Creates fanofprocess by passing the number of process through commandline args.
*
* @param argc
* @param argv[]
*
* @return 
*/
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    int pid;
    char c = 'a';	

int a = atoi(argv[1]);
printf("Parent id = %d\n",getpid());
    while(a != 0){		//process not created
	if( (pid = fork()) == -1){
		perror("Fork:");
		_exit(-1);
	} 
	if(pid == 0) {		//child process
		printf("%c%c%c%c%c\t %d\n", c,c,c,c,c,getpid());
		_exit(0);
	}
	a--;
    }	
	getchar();
    return 0;
}
