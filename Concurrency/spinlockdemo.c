#include<stdio.h>
#include<pthread.h>
int a,i=0;
pthread_spinlock_t s;
void *insert (void *);
int main()
{
int iret1,iret2,ret,pshared;
pthread_t tid1,tid2;
pthread_attr_t attr;
pthread_attr_init(&attr);
ret = pthread_spin_init(&s, pshared); 

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
pthread_spin_lock(&s);
scanf("%d",&a);
pthread_spin_unlock(&s);
printf("%d is inserted by %lx\n",a,pthread_self());
printf("b= %d\n",b);
}

