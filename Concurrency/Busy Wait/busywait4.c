/* busywait4.c   */
/* Simple pthread example: Busy Wait attempt 4                             */
/* This attempts to corrects the bug in raceexample.c                      */
/* To compile me for Linux, type:  gcc -o busywait4 busywait4.c -lpthread  */
/* To execute, type:  busywait4                                            */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>    // for microseconds sleep  
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    // for open(), read()
              



void * simple(void *);

#define NUM_THREADS 2
pthread_t tid[NUM_THREADS];      /* array of thread IDs */

int bignum = 0;
int flag[2] = {0,0};             /* whose trun is in its critical section?   */
int fd;

main( int argc, char *argv[] ) 
{
  int i, ret;

//   flag[0] = 1;                     /* start with P0      */
  fd = open("/dev/urandom", O_RDONLY);

  for (i=0; i<NUM_THREADS; i++) {
    pthread_create(&tid[i], NULL, simple, (void *)i); /* Note the thread arg  */
  }
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_join(tid[i], NULL);

  printf("\nmain() reporting that all %d threads have terminated\n", i);
  printf("I am main! bignum=%d\n", bignum);
  close(fd);
}  /* main */

  int c = '0';  
#define N 10


void * simple(void * parm){ 
  int i, j;
  int p = (int)parm;
  unsigned int delay;
  
  for(i = 0; i < N; i++) {
     flag[p] = 1;                  /*  I am entering critical section */  
     while(flag[1-p]){             /* if not my turn:                 */
     flag[p] = 0;                  /*   let the other enter its c.r   */
     read(fd, &delay, 4);          /*   get a random value            */
     usleep(delay % 100000);       /*   random wait upto 0.1 sec      */
     //usleep(10);
     flag[p] = 1;  /*   now I, keeping fingers crossed,  enter my c.r */
     }       

c = '0'+p;     
write(1, &c, 1);

// if(p == 1 && i == 5) while(1);
       j = bignum;
       j++;                         /* critical section */
       bignum = j;
     flag[p] = 0;                   /*  I am leaving critical section */
  }
}    

