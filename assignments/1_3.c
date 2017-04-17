#include <stdio.h> 
			#include <unistd.h> 
			int main(){ 
				pid_t child_p; 
				printf("Running ps with fork\n"); 
				child_p = fork(); 
				execlp("ps", "ps", "−ax", 0); 
				return 0; 
				}
