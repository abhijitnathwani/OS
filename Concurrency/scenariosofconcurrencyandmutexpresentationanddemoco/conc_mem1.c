#include<stdio.h>
#include<pthread.h>
int a,i=0;
pthread_mutex_t m;
void *insert (void *);
int main()
{
int iret1,iret2;
pthread_t tid1,tid2;
pthread_attr_t attr;
pthread_attr_init(&attr);

iret1=pthread_create(&tid1,&attr,insert,NULL);
iret2=pthread_create(&tid2,&attr,insert,NULL);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
printf("A = %d \n",a);
return 0;
}
void *insert(void * s)
{
int b=5;
printf("insert in a by %lx\n",pthread_self());
pthread_mutex_lock(&m);
scanf("%d",&a);
pthread_mutex_unlock(&m);
printf("%d is inserted by %lx\n",a,pthread_self());
printf("b= %d\n",b);
}

