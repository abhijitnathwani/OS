/**************************************************/
/* Another thread example.  This one shows that   */
/* pthreads in Linux can use both processors in   */
/* a dual-processor Pentium.                      */
/*                                                */
/* Usage:  a.out <num threads>                    */
/*                                                */
/* To compile me in Linux type:                   */
/*    gcc -o yetanother yetanother.c -lpthread          */
/**************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 10

long int sum; /* this data is shared by the thread(s) */
void *runner(void * param);

main(int argc, char *argv[])
{
  int num_threads, i;
  pthread_t tid[MAX_THREADS];     /* the thread identifiers  */
  pthread_attr_t attr; /* set of thread attributes */

  if (argc != 2) {
    fprintf(stderr, "usage:  a.out <integer value>\n");
    exit(-1);
  }

  if (atoi(argv[1]) <= 0) {
    fprintf(stderr,"%d must be > 0\n", atoi(argv[1]));
    exit(-2);
  }

  if (atoi(argv[1]) > MAX_THREADS) {
    fprintf(stderr,"%d must be <= %d\n", atoi(argv[1]), MAX_THREADS);
    exit(-3);
  }

  num_threads = atoi(argv[1]);
  printf("The number of threads is %d\n", num_threads);

  /* get the default attributes */
  pthread_attr_init(&attr);

  /* create the threads */
  for (i=0; i<num_threads; i++) {
    pthread_create(&(tid[i]), &attr, runner, (void *) i); 
    printf("Creating thread number %d, tid=%lu \n", i, tid[i]);
  }

  /* now wait for the threads to exit */
  for (i=0; i<num_threads; i++) { 
    pthread_join(tid[i],NULL);
  }
  printf("\nsum = %ld\n", sum); 
}

/* The thread will begin control in this function */
void *runner(void * param)
{
  int i;
  int threadnumber = (int) param;
  for (i=1; i<=10; i++){
      sum += i; 
      printf("Thread number [%d] i= (%d) sum=(%ld)\n ", threadnumber, i,sum);
  }    
  pthread_exit(0);
}


