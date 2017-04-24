
#include <pthread.h>
#include <stdio.h>

void * adder(void *);

#define NUM_THREADS 2 
pthread_t tid[NUM_THREADS];      /* array of thread IDs */
int bignum = 0;

main( int argc, char *argv[] ) 
{
  int i, ret;

/*  thr_setconcurrency(3); */
  for (i=0; i<NUM_THREADS; i++) {
    pthread_create(&tid[i], NULL, adder, NULL);
  }
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_join(tid[i], NULL);

  printf("main() reporting that all %d threads have terminated\n", i);
  printf("I am main! bignum=%d\n", bignum);

}  /* main */

  

void * adder(void * parm)
{
   int i=0,j=0;
   printf("I am a new thread!\n");

   for(i=0;i<5;i++) {
     j = bignum;
       j++;
       bignum =j;   /* BUG HERE: THIS IS NOT IN A MUTEX AND IS INCORRECT!! */
printf("big number = %d in Thread %lx\n",bignum,pthread_self());
}
   pthread_exit(0);
}    

