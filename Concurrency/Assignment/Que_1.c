#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_THREADS 2

struct LinkedList
{
	int data;
	struct LinkedList *next;
}*head=NULL;

pthread_t tid[MAX_THREADS];

int flag[2] = {0,1};

void append(void);
void * del(void*);
void display(void);

int main()
{

	int ch;

	

	printf("Select the choice by giving input as number :\n");
	
	do
	{
		printf("1. Append. 2. Display. 3. Delete at position. 4. Exit\nEnter your choice :");
		scanf( "%d" , &ch);
		switch(ch)
		{
			case 1:
                                append();
                                break;

			case 2:
                                display();
	                	break;                
			
			//case 3:
                        //        del();
                        //        break;

			case 4:
                                break;

			default :
				printf("Invalid choice.Please Insert choice from menu.\n");
				break;
		}
	}while(ch != 4 );

	
	pthread_create(&tid[0],NULL,del,(void *)0);
	pthread_create(&tid[1],NULL,del,(void *)1);


	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
		
	printf("Display by Master Thread.\n");
	display();
}


void append()
{
	int num;

		printf("Enter integer value to append in LinkedList:");
                scanf( "%d" , &num);

                struct LinkedList *temp,*tvp;
                temp = (struct LinkedList *)malloc(sizeof(struct LinkedList));

                if(head == NULL)
                {
                        temp->data = num;
                        temp->next = NULL;
                        head = temp;
                }
                else

                {       tvp = head;
                        while(tvp->next)
                                tvp = tvp->next;
                        tvp->next = temp;
                        temp->data = num;
                        temp->next = NULL;
                }


}


void *del(void * parm)
{
        int pos,count=1;
	int p = (int)parm;
	
	//if(tid[0] == pthread_self())
	if( p == 0 )
		pos = 2;	//thread 1 will delete 2nd node
	else
		pos = 4;	//thread 2 will delete 3rd node


	struct LinkedList *tvp,*prev;
	if(head == NULL)
		printf("LinkedList is Empty..!!\n");
	else
	{
		int c = '0';

		while(flag[1-p]); //waiting for turn
               
		tvp = head;
		

                if(pos==1)
                        if(tvp->next)
                                head = tvp->next;
                        else
                                head=NULL;
                else
                {
			flag[p] = 1;	// Entering critical section
                        while( count != pos)
                        {
                                prev = tvp;
                                tvp = tvp->next;
                                count++;
                        }
                        prev->next = tvp->next;
                        free(tvp);
			printf("Display by thread %d.\n",p);
			display();
			flag[1-p] = 1;
			flag[p]=0;    //leaving critical section
                }
	
	}//end of else
}



void display()
{
        int i=1;
        struct LinkedList *tvp=head;
        while(tvp)
        {
                printf("Data of Node %d : %d\n",i++,tvp->data);
                tvp = tvp->next;
        }
}

