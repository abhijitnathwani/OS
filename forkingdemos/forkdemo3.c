#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    int pid;
    char c = 'a';	
    
    c = getchar();
    while(c != 'z'){
	if( (pid = fork()) == -1){
		perror("Fork:");
		_exit(-1);
	} 
	else if(pid == 0) {
		printf("%c%c%c%c%c\n", c,c,c,c,c);
		_exit(0);
	} else 
{
printf("pid is %d \n",pid);
c = getchar();
    }	}
    return 0;
}
