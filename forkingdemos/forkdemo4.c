#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sleeprand(){
	int r;
	r = 1+(int) (1000000.0*rand()/(RAND_MAX+1.0));
//	printf("%d microsec sleep\n", r);
	usleep(r);
}
int x = 999;

int main(int argc, char *argv[]){
	int pid;
//	int x = 999;
        int *px = &x;
        
	if( (pid = fork()) == -1){
		perror("Fork:");
		_exit(-1);
	}
	if(pid == 0) {
		x = 222;
		
		printf("1. I am child:  x = %d,address of x is %p, px = %p\n", x,&x, px);
		sleeprand();
		printf("2. I am child:  x = %d,address of x is %p, px = %p\n", x,&x, px);
		sleeprand();
		printf("3. I am child:  x = %d,address of x is %p, px = %p\n", x,&x, px);
		sleeprand();
		px = &x;
		
		printf("4. I am child:  x = %d,address of x is %p, px = %p\n", x, &x,px);
		sleeprand();
		printf("5. I am child:  x = %d,address of x is %p, px = %p\n", x,&x, px);
	} else {
		printf("1. I am parent:  x = %d,address of x is %p, px = %p\n", x,&x, px);
		sleeprand();

		printf("2. I am parent:  x = %d,address of x is %p, px = %p\n", x,&x, px);
		sleeprand();

		printf("3. I am parent:  x = %d,address of x is %p, px = %p\n", x,&x, px);
		sleeprand();
	
		printf("4. I am parent:  x = %d,address of x is %p, px = %p\n", x,&x, px);
		sleeprand();

		printf("5. I am parent:  x = %d,address of x is %p, px = %p\n", x,&x, px);
	}
	return 0;
}
