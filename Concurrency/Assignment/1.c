#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
struct Listnode
{
    int data;
    struct Listnode *next;
}*head;

int turn=3;             // to give chance to the second thread

void appendNode(int num)
{
  struct Listnode *newNode, *nodePtr;
   newNode =(struct Listnode*)malloc(sizeof(struct Listnode));
   newNode->data = num;
   newNode->next = NULL;
   if (!head)
     head = newNode;
   else	
    {
     nodePtr = head;
      while (nodePtr->next)
        nodePtr = nodePtr->next;
      nodePtr->next = newNode;
    }
}

void insert(int num)
{
  struct Listnode *newNode, *nodePtr, *previousnode;
  newNode =(struct Listnode*)malloc(sizeof(struct Listnode));
  newNode->data = num;
  if (!head)  {
    head = newNode;
    newNode->next = NULL;
   }
  else
   {
    nodePtr = head;
     while (nodePtr->next!=NULL && nodePtr->data < num) {
      previousnode = nodePtr;
      nodePtr= nodePtr->next;
      }
       if(previousnode==NULL)
       {
          head=newNode;
          newNode->next = nodePtr;
       }
       else
       {
         previousnode->next=newNode;
         newNode->next=nodePtr;
       }
   }
}

void delete(int num)
{
  struct Listnode *nodePtr, *previousnode;
   if(head->data==num)
    {
     nodePtr=head->next;
     head->data=nodePtr->data;
     head->next=nodePtr->next;
    }
   else
    {
     nodePtr=head;
     while(nodePtr!=NULL && nodePtr-> data != num)
     {
      previousnode=nodePtr;
      nodePtr=nodePtr->next;
     }
     previousnode->next=nodePtr->next;
  }
}
 
void display()
{
  struct Listnode *nodePtr;
  nodePtr=head;
  while(nodePtr)
   {
     printf("%d ",nodePtr->data);
     nodePtr= nodePtr->next;
   }
   printf("\n");
}


void *deletepos(int pos)
{
   int i, counter=0;
   struct Listnode *nodePtr,*previousnode;
  
   for(i=0;i<=2;i++)  { 
    while(turn!=pos); 
    
    nodePtr=head;
    if(pos==1)
    {
        head=nodePtr->next;
    }
    else
    {
      while(nodePtr!=NULL)
        {
            nodePtr=nodePtr->next;
            counter++;  
        }
        if(pos>0&&pos<=counter)
        {
            nodePtr=head;
            for(i=1;i<pos;i++)
            {
                previousnode=nodePtr;
                nodePtr=nodePtr->next;
            }
            previousnode->next=nodePtr->next;
        }
        else
        {
            printf("Position out of range\n");
        }
        printf("Element Deleted\n");
    }
   turn=pos-1;
 }
}


int main()
{
    int a,num,inum,dnum,i;
    pthread_t tid[2];

    while(1)  {
    printf("Enter\n1- for APPEND \n2- for INSERT\n3- for DISPLAY\n4- for DELETE\n5- for DELETE  using thread\n6- EXIT\n");
    printf("Enter Your Choice ");
    scanf("%d",&a);
    switch(a) {
       case 1:         
         printf("Enter element ");
         scanf("%d",&num);
         appendNode(num);
         break;
      case 2:
         printf("Enter element ");
         scanf("%d",&inum);
         insert(inum);
         break;
      case 3:
         display();
         break;
      case 4:
	 printf("Enter element ");
         scanf("%d",&dnum);
 	 delete(dnum);
	 break;
       case 5: {
         for (i=0; i<2; i++) {
            pthread_create(&tid[i], NULL, deletepos, ((void *)i+2)); /* Note the thread arg  */
          }
        for ( i = 0; i < 2; i++)
             pthread_join(tid[i], NULL);
          }
         break;
      case 6:
         exit(0);
      default:
         printf("Invalid input\n" );
   }
 }
}
