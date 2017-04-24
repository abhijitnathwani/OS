#include<stdio.h>
#include<pthread.h>
int a;
void *insert (void *);
int main(){
//	int i=0;
	int iret1,iret2;
	pthread_t tid1,tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	iret1=pthread_create(&tid1,&attr,insert,NULL);
	iret2=pthread_create(&tid2,&attr,insert,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("a =  %d \n",a);
	return 0;
}
void *insert(void * s)
{
//int i=0;


printf("insert in a\n");
scanf("%d ",&a);
printf("%d is inserted by %lx\n",a,pthread_self());

}

