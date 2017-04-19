#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>
#include<fcntl.h>
void *print_message_function (void *ptr);

main ()
{
  pthread_t thread1, thread2;
  pthread_attr_t attr;
  int ret;
  pthread_attr_init(&attr);
  ret=pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  char *message1 = "I am Thread 1";
  char *message2 = "I am Thread 2";
  int iret1=5, iret2=10;
//printf("Ret value after setting attribute is %d\n",ret);
  /* Create independent threads each of which will execute function */
  printf("my pid = %d\n",getpid());
  iret1 = pthread_create (&thread1, &attr, print_message_function,
			  (void *) message1);
  iret2 = pthread_create (&thread2, &attr, print_message_function,
		    (void *) message2);
	
  /* Wait till threads are complete before main continues. Unless we  */
  /* wait we run the risk of executing an exit which will terminate   */
  /* the process and all threads before the threads have completed.   */

/* */
 pthread_join (thread1, NULL);
pthread_join (thread2, NULL);
/* */
  printf ("Thread 1 returns: %d\n", iret1);
  printf ("Thread 2 returns: %d\n", iret2);
  exit (0);
}

void *print_message_function (void *ptr){
  char *message;
  int fd=open("hello.txt",O_WRONLY);
  message = (char *) ptr;
  //pthread_detach(pthread_self());
  write(fd,message,strlen(message));

//  printf ("%s \n", message);
}
