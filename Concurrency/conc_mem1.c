#include<stdio.h>
#include<pthread.h>
int a,i=0;
pthread_mutex_t m;

void *insert ();
int b=5;


pthread_mutexattr_t attr;




int main()
{
int iret1,iret2;
pthread_t tid1,tid2;
pthread_mutexattr_init(&attr);
pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
pthread_mutex_init(&m, &attr);

pthread_attr_t attr;
pthread_attr_init(&attr);

iret1=pthread_create(&tid1,&attr,insert,NULL);
//iret2=pthread_create(&tid2,&attr,insert,NULL);
pthread_join(tid1,NULL);
//pthread_join(tid2,NULL);
printf("A = %d \n",a);
printf("%d\n", b );
return 0;
}
void *insert()
{

printf("insert in a by %lx\n",pthread_self());
pthread_mutex_lock(&m);
printf("%d\n",b++ );
insert();
pthread_mutex_unlock(&m);
printf("%d is inserted by %lx\n",a,pthread_self());
printf("b= %d\n",b);
}

