  /* busywait5.c   */
/* Simple pthread example: Busy Wait attempt 5 : Dekker's Solution         */
/* This attempts to corrects the bug in raceexample.c                      */
/* To compile me for Linux, type:  gcc -o busywait5 busywait5.c -lpthread  */
/* To execute, type:  busywait5                                            */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>    // for microseconds sleep  
              



void * simple(void *);

#define NUM_THREADS 2
pthread_t tid[NUM_THREADS];      /* array of thread IDs */

int bignum = 0;
int flag[2] = {0,0};             /* whose trun is in its critical section?   */
int turn;

main( int argc, char *argv[] ) 
{
  int i, ret;

  turn = 1;                     /* start with P1      */

  for (i=0; i<NUM_THREADS; i++) {
    pthread_create(&tid[i], NULL, simple, (void *)i); /* Note the thread arg  */
  }
  for ( i = 0; i < NUM_THREADS; i++){
  
  
    printf("[%d] ", i);
    pthread_join(tid[i], NULL);
    printf("I am main! bignum=%d\n", bignum);
  }  

  printf("\nmain() reporting that all %d threads have terminated\n", i);
  printf("I am main! bignum=%d\n", bignum);
}  /* main */

  int c = '0';  
#define N 10


void * simple(void * parm){ 
  int i, j;
  int p = (int)parm;
  
  for(i = 0; i < N; i++) {
// if(p == 1 && i == 5) while(1);      /* stop outside c.r.           .....  [I]  */
  
    if(turn==1)
     flag[1-p] = 0;
    else if(turn==0)
     flag[1-p]=1;                  /*  I am entering critical section */  
     while(flag[1-p]){             /* if not my turn:                 */
         if(turn == (1-p)){
             flag[p] = 0;                  /*   let the other enter its c.r   */
             while(turn == (1-p));
             flag[p] = 1;  /*   now I, keeping fingers crossed,  enter my c.r */
         }    
     }       
     
// if(p == 1 && i == 5) while(1);      /* stop in side decision region  ----   [II]  */

c = '0'+p;                          /* begin critical section      */  
write(1, &c, 1);

//  if(p == 1 && i == 5) while(1);    /* stop  inside c.r.           ----   [III]  */
       j = bignum;
       j++;                         /* critical section */
       bignum = j;                  /* end critical section */
     turn = 1-p;                      /*  let the other have turn       */
     flag[p] = 0;                   /*  I am leaving critical section */
  }
 
}    

