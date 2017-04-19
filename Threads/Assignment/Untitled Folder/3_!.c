
#include <unistd.h>  // sleep()
#include <pthread.h> 
#include <stdio.h>   
#include <stdlib.h>  // EXIT_SUCCESS
#include <string.h>  // strerror() 
#include <errno.h>

/***************************************************************************/
/* our macro for errors checking                                           */
/***************************************************************************/
#define COND_CHECK(func, cond, retv, errv) \
if ( (cond) ) \
{ \
   fprintf(stderr, "\n[CHECK FAILED at %s:%d]\n| %s(...)=%d (%s)\n\n",\
              __FILE__,__LINE__,func,retv,strerror(errv)); \
   exit(EXIT_FAILURE); \
}

#define ErrnoCheck(func,cond,retv)  COND_CHECK(func, cond, retv, errno)
#define PthreadCheck(func,rc) COND_CHECK(func,(rc!=0), rc, rc)

/*****************************************************************************/
/* thread- dummy thread                                                      */
/*****************************************************************************/
int a=10;
int c=0;
void* thread(void* ignore)
{
   sleep(1);
//while(1)
{
  write(1,".",1);
}
    printf("thread1 c=%d\n",c);
   
   return NULL;
}
void* thread1(void* ignore)
{
   //sleep(5);
      //printf("in thread 2 a= %d  and c= %d\n",a,c);
    printf("NULL\n");
    //while(1);
    c=a;
    //printf("in thread2 c = %d\n",c);
   return NULL;
}

/*****************************************************************************/
/* detach_state. Print detachstate of a thread.                              */
/*****************************************************************************/
/* 
 * We find out indirectly if a thread is detached using pthread_join().  
 * If a thread is detached, then pthread_join() fails with EINVAL. 
 * Otherwise the thread is joined, and hence was joinable. 
 *
 */
void detach_state(
   pthread_t   tid,  // thread to check detach status
   const char *tname // thread name
   )
{
   int rc; // return code

   rc = pthread_join(tid, NULL);
   if ( rc==EINVAL ) 
   {
      printf("%s is detached\n", tname);
   }
   else if ( rc==0 )  
   {  
      printf("%s was joinable\n", tname);
   }
   else 
   {
      printf("%s: pthread_join() = %d (%s)\n", 
             tname, rc, strerror(rc)
            );
   }
}

/*****************************************************************************/
/* main- main thread                                                         */
/*****************************************************************************/
int main()
{
//   fflush(stdout);
   pthread_t tid1, tid2, tid3; // thread 1,2 and 3.
   pthread_attr_t attr;        // thread's attribute
   int rc;  // return code


   /*--------------------------------------------------------*/
   /* 2nd test: detach thread from main thread               */
   /*--------------------------------------------------------*/
   rc = pthread_create(&tid2, NULL, thread1, NULL);
   PthreadCheck("pthread_create", rc);
   rc = pthread_detach(tid2);
   PthreadCheck("pthread_detach", rc);
   detach_state(tid2, "thread2"); // expect: detached
   //sleep(3);
   /*--------------------------------------------------------*/
   /* 3rd test: create detached thread                       */
   /*--------------------------------------------------------*/

   // set detachstate attribute to DETACHED
   //
   rc=pthread_attr_init(&attr);
   PthreadCheck("pthread_attr_init", rc);
   rc=pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   PthreadCheck("pthread_attr_setdetachstate", rc);

   // create thread now 
   //
   rc = pthread_create(&tid3, &attr, thread1, NULL);
   PthreadCheck("pthread_create", rc);
   detach_state(tid3, "thread3");
   sleep(3);
//while(1);
   /*--------------------------------------------------------*/
   /* 1st test: normal thread creation                       */
   /*--------------------------------------------------------*/
   rc = pthread_create(&tid1, NULL, thread, NULL);
   PthreadCheck("pthread_create", rc);
   detach_state(tid1, "thread1"); // expect: joinable 
   sleep(3);
  // rc = pthread_detach(tid1);
   // PthreadCheck("pthread_detach", rc);
   // detach_state(tid1, "thread2"); // expect: detached

   /*--------------------------------------------------------*/
   /* that's all folks!                                      */
   /*--------------------------------------------------------*/

   return EXIT_SUCCESS;
}