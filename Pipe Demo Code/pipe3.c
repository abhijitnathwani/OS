/*
 * 	pipe3.c
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pipe_fd[2];

void open_pipe(int *fd){
	if(pipe(fd) == -1)
		perror("could not open pipe");
}

int send_to_pipe(int *fd, char *s){
	int count = 0;
	printf("writing to %d\n", fd[1]);	
	do{
		if(write(fd[1],s,1) == -1)
			perror("snd");
		count++;
	} while(*s++); /* '\0' also should be sent */
	
	return count;
}

int receive_frm_pipe(int *fd, char *b){
	int count = 0;
	printf("reading from %d\n", fd[0]);	
	if(read(fd[0], b, 1) == -1)
		perror("rcv1");
	while(*b){
		count++;
		b++;
		if(read(fd[0], b, 1) == -1)
			perror("rcv2");
	}
	return count;
}


int main(int argc, char *argv[]){
	char buffer[10000];
	int i, n;
	
	if(argc > 1)
		n = atoi(argv[1]);
	else    n = 16;
	open_pipe(pipe_fd);
	printf("main: pipe opened %d %d\n", pipe_fd[0], pipe_fd[1]);
	for(i=0;i<n;i++){
		send_to_pipe(pipe_fd, "abcdefghijklmno");
	}
	printf("main: sent to pipe %d char.\n", n*16);
	for(i=0;i<n;i++){
		receive_frm_pipe(pipe_fd, buffer);
	}
	printf("main: we received %d char\n Data is %s", i*16,buffer);
	close(pipe_fd[0]);
}

