#include <stdio.h>
#include <pthread.h>


int count;
pthread_mutex_t m;

void *thread1();
void *thread2();



pthread_mutexattr_t attr;
pthread_spinlock_t s;




int main()
{
		int iret1,iret2,ret,pshared;
		pthread_t tid1,tid2;
		ret = pthread_spin_init(&s, pshared); 
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		iret1=pthread_create(&tid1,NULL,thread1,NULL);
		iret2=pthread_create(&tid2,NULL,thread2,NULL);
		pthread_join(tid1,NULL);
		pthread_join(tid2,NULL);
		return 0;
}
void *thread1()
{
	printf("In thread1\n");
	while(count<=10)
	{
		if((count>=0 && count<4) || (count>7 && count<=10))
		{
			
			printf("\ncount in thread1: %d\n",count );
			count++;

		}
	}

}

void *thread2()
{
	while(count<=10)
	{
		if((count>=4 && count<=7))
		{

			printf("\ncount in thread2: %d\n",count );
			count++;

		}
	}
}
