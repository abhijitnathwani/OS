#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function (void *ptr);
void getthreadattributes(pthread_t thread);

main ()
{
  pthread_t thread1, thread2;
  char *message1 = "I am Thread 1";
  char *message2 = "I am Thread 2";
  int iret1=5, iret2=10;
  
  pthread_attr_t attr;
  
  

  /* Create independent threads each of which will execute function */

  iret1 = pthread_create (&thread1, NULL, print_message_function,
			  (void *) message1);
  
  /* Wait till threads are complete before main continues. Unless we  */
  /* wait we run the risk of executing an exit which will terminate   */
  /* the process and all threads before the threads have completed.   */

/* */
 pthread_join (thread1, NULL);
 
 getthreadattributes(thread1);

/* */
  printf ("Thread 1 returns: %d\n", iret1);


  exit (0);
}

void *print_message_function (void *ptr){
  char *message;
  message = (char *) ptr;
  printf ("%s \n", message);
  
}
void getthreadattributes(pthread_t thread)
{
  pthread_attr_t attr;

  int ret,s,scope,detachstate,inherit;
  ret=pthread_getattr_np(thread,&attr);
  size_t guardsize,stacksize;

  s = pthread_attr_getguardsize(&attr, &guardsize);
  ret = pthread_attr_getscope(&attr, &scope);
  ret = pthread_attr_getstacksize(&attr, &stacksize);
  ret = pthread_attr_getdetachstate (&attr, &detachstate);
  ret=pthread_attr_getinheritsched(&attr, &inherit);
  printf("\nThread Attributes:\n\n");
  printf("Guard Size: %d\n", guardsize);
  printf("Stack Size: %d\n", stacksize);
  printf("Detach State: %d\n", detachstate);
  printf("Inherit Sched: %d\n", inherit);
  printf("Scope: %d\n", scope);
}