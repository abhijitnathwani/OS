/* busywait2.c   */
/* Simple pthread example: Busy Wait attempt 2                             */
/* This attempts to correct the bug in raceexample.c                      */
/* Fails with mutex like functionality. but not able to solve racing problem*/
/* To compile me for Linux, type:  gcc -o busywait2 busywait2.c -lpthread  */
/* To execute, type:  busywait2                                            */

#include <pthread.h>
#include <stdio.h>

void * simple(void *);

#define NUM_THREADS 2
pthread_t tid[NUM_THREADS];      /* array of thread IDs */
pthread_mutex_t m;
int bignum = 0;
int flag[2] = {0,0};             /* whose trun is in its critical section?   */

main( int argc, char *argv[] ) 
{
  int i, ret;

  // flag[0] = 1;                     /* start with P0      */

  for (i=0; i<NUM_THREADS; i++) {
    pthread_create(&tid[i], NULL, simple, (void *)i); /* Note the thread arg  */
  }
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_join(tid[i], NULL);

  printf("\nmain() reporting that all %d threads have terminated\n", i);
  printf("I am main! bignum=%d\n", bignum);

}  /* main */

  int c = '0';  
#define N 10
void * simple(void * parm){ 
  int i, j;
  int p = (int)parm;
//pthread_mutex_lock(&m);
  for(i = 0; i < N; i++) {
     while(flag[1-p]);       /* wait if not my turn */

c = '0'+p;     
write(1, &c, 1);
    // flag[1-p]=1;
     flag[p] = 1;                  /*  I am entering critical section */

       j = bignum;
       j++;                         /* critical section */
       bignum = j;

flag[p] = 0;                   /*  I am leaving critical section */

  }
//pthread_mutex_unlock(&m);
}    

