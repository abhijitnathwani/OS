#include<stdio.h>
#include<stdlib.h>

struct node{
int data;
struct node *next;
}*start=NULL;

struct node *tmp_node;
struct node *prev;
int rs,count=0;
struct node *current;
struct node *lct;

#define NUM_THREADS 2
void * dis(void *);
void * del(void *);
pthread_mutex_t lc;
pthread_t tid[NUM_THREADS];      /* array of thread IDs */

int bignum = 0;
int turn; 

void create()
{
  struct node *new_node;

  new_node=(struct node *)malloc(sizeof(struct node));
   
  printf("Enter the data : ");
  scanf("%d",&new_node->data);
  new_node->next=NULL;
  
  if(start==NULL)
  {
  start=new_node;
  current=new_node;
  printf("Link list created.");
  }
  else
  {
  printf("\t*** At start 1.\tAt End 2.\tAt Location 3.\n");
  scanf("%d",&rs);
	if(rs==1){
		new_node->next=start;
		start=new_node;
	}
	else if(rs==2){
		current->next=new_node;
		current=new_node;
	}
	
  }

}

void delete(){
   
  if(start==NULL)
  {
  printf("No Node in the list");
  }
  else
  {
  printf("\t*** At start 1.\tAt End 2.***\n");
  scanf("%d",&rs);
        if(rs==1){
		tmp_node=start->next;
		start=tmp_node;
        }
        else if(rs==2){
		lct=start;
		printf("%d",lct->data);
		while(lct->next != current){
			lct=lct->next;
   		}
		current=lct;
		current->next=NULL;
		
        }
  } 
}
void * del(void *param){
if(start==NULL)
  {
  printf("No Node in the list");
  }
  else
  {
  printf("\t*** At start 1.\tAt End 2.***\n");
  scanf("%d",&rs);
        if(rs==1){
		tmp_node=start->next;
		start=tmp_node;
        }
        else if(rs==2){
		lct=start;
		printf("%d",lct->data);
		while(lct->next != current){
			lct=lct->next;
   		}
		current=lct;
		current->next=NULL;
		
        }
  } 
}

void display()
{
struct node *dis_node;
// printf("The Linked List :");
 dis_node=start;
 while(dis_node!=NULL)
   {
   printf(": %d ",dis_node->data);
   dis_node=dis_node->next;
   }
  printf("\n");
  printf("NULL\n");
}

void *dis(void *data){
	pthread_mutex_lock(&lc);
	struct node *dis_node;
	dis_node=start;
	while(dis_node!=NULL)
	{
		printf(": %d ",dis_node->data);
		if(dis_node->data==data){
			pthread_mutex_unlock(&lc);
		}	
		dis_node=dis_node->next;
	}
	printf("\n");
	printf("NULL\n");
}

int main(){
   int choice;
   int val;
    while (1)
    {
	printf("\nNode");
        printf("\nInsert :1\tDelete :2\tDisplay :3\tQuit :4\tRCU :5\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                create();
                break;
            case 2:
                delete();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(1);
	    case 5:
		printf("Enter number of node to delete\n");
		scanf("%d",&val);
		pthread_create(&tid[0], NULL,dis,(void*)val); /* Note the thread arg  */
		pthread_create(&tid[1], NULL,del,NULL); /* Note the thread arg  */
            default:
                printf("Wrong choice \n");
        } //End of switch

    } //End of while

return 0;
}
