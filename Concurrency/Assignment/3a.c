#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX 50

int queue[MAX];
int rear=-1;
int front=-1;
pthread_mutex_t m;        

void *insert()               
{    
  int num,i;
  if (rear==MAX-1)
   printf("Queue Overflow \n");
  else
    {
      if(front==-1)           
       front=0;

     for(i=0;i<49;i++)
        {
          queue[rear]=i;
          rear=rear+1;
        } 
       printf("\nElements %d\n",i); 
    }
} 

void *delete()
{
  pthread_mutex_lock(&m);
  if (front==-1||front>rear)  {
    printf("Queue Underflow \n");
    return ;
   }
  else
   {
     printf("\nDeleted element %d\n",queue[front]);
     front=front+1;
    } 
  pthread_mutex_unlock(&m);
} 

void display()
{
  int i;
  if (front==-1)
     printf("Queue is empty \n");
  else
   {
     printf("Queue is : \n");
     for(i=front;i<=rear;i++)
      printf("%d ",queue[i]);
     printf("\n");
   }
}

int main()
{
  int ch, i;
  pthread_t tid1,tid2,tid3;
  display();
  pthread_create(&tid1,NULL,insert,NULL);
//  sleep(1);
  pthread_create(&tid2,NULL,delete,NULL);  
  //sleep(1);
  pthread_create(&tid3,NULL,delete,NULL);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);

//  sleep(1);
 // display();
}
