#include <pthread.h>
#include <stdio.h>

void * fact(void *);

#define NUM_THREADS 2
pthread_t tid;      /* array of thread IDs */
pthread_mutex_t m;
int main()
{
	int n;
	
	printf("ENter the number for factorial: \n");
	scanf("%d",&n);
	pthread_create(&tid,NULL,fact,(void *)n);

	pthread_join(tid,NULL);
	//printf("factorial: %d\n",(int *)fact);
	printf("Thread execution complete \n");
	
}
void * fact(void * parm)
{ 
  

}    


