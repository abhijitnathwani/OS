/* busywait1.c   */
/* Simple pthread example: Busy Wait attempt 1                             */
/* This attempts to corrects the bug in raceexample.c                      */
/* To compile me for Linux, type:  gcc -o busywait1 busywait1.c -lpthread  */
/* To execute, type:  busywait1                                            */

#include <pthread.h>
#include <stdio.h>

void * simple(void *);

#define NUM_THREADS 2
pthread_t tid[NUM_THREADS];      /* array of thread IDs */

int bignum = 0;
int turn;                       /* whose trun is it?   */

main( int argc, char *argv[] ) 
{
  int i, ret;

  turn = 0;                     /* start with P0      */

  for (i=0; i<NUM_THREADS; i++) {
    pthread_create(&tid[i], NULL, simple, (void *)i); /* Note the thread arg  */
  }
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_join(tid[i], NULL);

  printf("\nmain() reporting that all %d threads have terminated\n", i);
  printf("I am main! bignum=%d\n", bignum);

}  /* main */

  char c = '0';  
#define N 10
void * simple(void * parm){ 
  int i, j;
  int p = (int)parm;
  for(i = 0; i < N; i++) {
     while(turn != p);       /* wait if not my teurn */

       c = '0'+p;     
       write(1, &c, 1);
       j = bignum;
       j++;                         /* critical section */
       bignum = j;
     turn = 1 - p;                      /* yeild to the other  */
  }
}    

