#include <pthread.h>
#include <stdio.h>

void * func1();
void * func2();

#define NUM_THREADS 2
pthread_mutex_t mut1;
pthread_mutex_t mut2;
int A = 0;
int B = 0;

main( int argc, char *argv[] ) 
{
  int iret1,iret2;
  pthread_t thread1, thread2;
  iret1 = pthread_create (&thread1, NULL, func1,NULL);
  iret2 = pthread_create (&thread2, NULL, func2,NULL);
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
  printf("\nmain() reporting that all threads have terminated\n") ;
  //printf("I am main! A=%d\nB=%d\n", A,B);

}  /* main */

  char c = '0';  
#define N 10
void * func2()
{ 
  printf("Thread 1\nA=%d\nB=%d\n",A,B);
  pthread_mutex_lock(&mut1);
  A = 1;
  c = '0'+A;     
  pthread_mutex_lock(&mut2);
  B = 1;
  c = '0'+B;
  printf("Thread 1\nA=%d\nB=%d\n",A,B);
  pthread_mutex_unlock(&mut2);
  pthread_mutex_unlock(&mut1);
  
}    

void * func1()
{ 
   printf("Thread 2\nA=%d\nB=%d\n",A,B);
  pthread_mutex_lock(&mut2);
  B = 2;
  c = '0'+B;     
  pthread_mutex_lock(&mut1);
  A = 2;
  c = '0'+A;
  printf("Thread 2\nA=%d\nB=%d\n",A,B);
  pthread_mutex_unlock(&mut1);
  pthread_mutex_unlock(&mut2);
   
}    

