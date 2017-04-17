/*
 * 	pipe1.c
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pipe_fd[2];

void open_pipe(int *fd){
	if(pipe(fd) == -1)
		perror("could not open pipe");
}

int main(int argc, char *argv[]){
	open_pipe(pipe_fd);
	printf("pipe opened %d %d\n", pipe_fd[0], pipe_fd[1]);
}
