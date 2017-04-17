#include <unistd.h> 
			#include <stdio.h> 
			int main(){ 
				pid_t pid; 
				printf("Running ps again with fork\n"); 
				pid = fork(); 
				if ( pid == 0 ) { // in the child, do exec 
				execlp("ps", "ps", "−ax", 0); 
				} 
				else if (pid < 0){ // failed to fork 
				printf("fork failed.\n"); 
				exit(1); 
				} 
				else {// parent 
				wait(NULL); 
				} 
				exit(0); 
				}
