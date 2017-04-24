/**************************************************/
/* Another thread example.  This one shows that   */
/* pthreads in Linux can use both processors in   */
/* a dual-processor Pentium.                      */
/*                                                */
/* Usage:  a.out <num threads>                    */
/*                                                */
/* To compile me in Linux type:                   */
/*    gcc -o another another.c -lpthread          */
/**************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 10

int sum; /* this data is shared by the thread(s) */
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

  /* get the default attributes */
  pthread_attr_init(&attr);

  /* create the threads */
  for (i=0; i<num_threads; i++) {
    pthread_create(&tid[i], &attr, runner, NULL); 
  }

  /* now wait for the threads to exit */
  for (i=0; i<num_threads; i++) {
    pthread_join(tid[i],NULL);
  }
}

/* The thread will begin control in this function */
void *runner(void * param)
{
  int i = 1;
long unsigned int id;  
while(i) {
//    i = ++i % 3;
i=i++;
printf("i is %d \n ",i);
id=pthread_self();
printf("My id is %lx\n",id);
    sum = sum+i;
printf("sum is %d at thread %lx\n",sum,id);
  }
//  pthread_exit(0);
}


