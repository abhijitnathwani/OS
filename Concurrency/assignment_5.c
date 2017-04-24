/*  Pattern: 1111100000 */ 
#include <pthread.h>
#include <stdio.h>

void * adder(void *);

pthread_mutex_t m,p;
int t1=0,t2=0;

#define NUM_THREADS 2 
pthread_t tid[NUM_THREADS];      /* array of thread IDs */
int bignum = 0;

main( int argc, char *argv[] ) 
{
  int i=0, ret;

  /*thr_setconcurrency(3); */
  
  for (i=0; i<NUM_THREADS; i++) {
    pthread_create(&tid[i], NULL, adder, (void *)i);
    //sleep(1);
  }

    
  for ( i = 0; i < NUM_THREADS; i++)
       pthread_join(tid[0], NULL); 
  
  printf("main() reporting that all %d threads have terminated\n", i);
  printf("I am main! bignum=%d\n", bignum);

}  /* main */

  

void * adder(void * parm)
{
   int i=0,j=0;
   int k=(int *)parm;

   printf("I am a new thread!\n ");
   //pthread_mutex_lock(&m);
  t2=1;
   for(i=0;i<5;i++) {
     j = bignum;
       j++;
       bignum =j;   /* BUG HERE: THIS IS NOT IN A MUTEX AND IS INCORRECT!! */

       if(t1==0 && k==0)
       {
        
            printf("big number = %d in Thread %lx\t %d \n",bignum,pthread_self(),(int *)parm);
            t1=1;
            
        //    pthread_mutex_unlock(&m);
      }
      else if(k==1 && t1==1)  
      {
        //pthread_mutex_lock(&m);
        printf("big number = %d in Thread %lx\t %d \n",bignum,pthread_self(),(int *)parm);
       // pthread_mutex_unlock(&m);
        t1=0;
        
      }
}
//pthread_mutex_unlock(&m);
   pthread_exit(0);
}    

