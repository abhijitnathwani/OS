#include<stdio.h>
#include<stdlib.h>
struct ListNode
{
	int value;
	struct ListNode *next;
};
struct ListNode *head=NULL;

void appendNode(int num);
void displayList();
void insertNode(int num);
void deleteNode(int num);
void addNode(int num, int n);
void *deleteRCU(void *);
void *displayRCU(void *);

pthread_mutex_t lock;
pthread_t thread1, thread2;

int count=0;
int main()
{
	int num,c=0,loc,pos=0;
	do
	{
		printf("\n----------Singly Linked List----------\n");
		printf("1. Insert at Head\n2. Insert at Tail\n3. Insert at particular Node\n4. Delete Node\n5. Display List\n6. RCU\n7. Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				printf("Enter the value: ");
				scanf("%d",&num);
				insertNode(num);
				printf("\nList Updated.");
				break;
			case 2:
				printf("Enter the value: ");
				scanf("%d",&num);
				appendNode(num);
				printf("\nList Updated.");
				break;
			case 3:
				printf("\nEnter Location: ");
				scanf("%d",&loc);
				printf("\nEnter the value: ");
				scanf("%d",&num);
				addNode(num,loc);
				printf("\nList Updated.");
				break;
			case 4:
				displayList();
				printf("Enter the value of the node to be deleted: ");
				scanf("%d",&num);
				deleteNode(num);
				printf("\nList Updated.");
				break;
			case 5:
				displayList();
				break;
			case 6:
				printf("Enter the position of node to be deleted: \n");
				scanf("%d",&pos);
				pthread_create(&thread1,NULL,deleteRCU,(void *)pos);
				pthread_create(&thread2,NULL,displayRCU,(void *)pos);
				pthread_join(thread1,NULL);
				pthread_join(thread2,NULL);
				break;
			case 7:
				exit(1);
				break;
		}
	}while(c!=7);
	return 0;
}
void appendNode(int num)
{
	struct ListNode *newNode, *nodePtr;
	newNode=malloc(sizeof(struct ListNode));
	newNode->value=num;
	newNode->next = NULL;
	if(!head)
		head=newNode;
	else{
		nodePtr=head;
		while(nodePtr->next)
			nodePtr=nodePtr->next;
		nodePtr->next=newNode;
	}
}
void insertNode(int num)
{
	struct ListNode *newNode, *nodePtr,*previousNode;
	newNode=malloc(sizeof(struct ListNode));
	newNode->value=num;
	newNode->next = NULL;
	if(!head)
		head=newNode;
	else{
		nodePtr=head;
		while(nodePtr != NULL && nodePtr->value < num){
			previousNode = nodePtr;
			nodePtr=nodePtr->next;
		}
		if(previousNode==NULL)
		{
			head=newNode;
			newNode->next=nodePtr;
		}
		else
		{
			previousNode->next=newNode;
			newNode->next=nodePtr;
		}
	}
}
void addNode(int num, int n)
{
	struct ListNode *newNode, *nodePtr, *previousNode;
	newNode=malloc(sizeof(struct ListNode));
	newNode->value=num;
	newNode->next=NULL;
	int i=0;
	if(!head)
		head=newNode;
	else{
		nodePtr=head;
		while(nodePtr!=NULL && i<n){
			previousNode = nodePtr;
			nodePtr=nodePtr->next;
			i++;
		}
		if(previousNode==NULL)
		{
			head=newNode;
			newNode->next=nodePtr;
		}
		else
		{
			previousNode->next=newNode;
			newNode->next=nodePtr;
		}
	}
}
void deleteNode(int num)
{
	struct ListNode *nodePtr,*previousNode;
	if(!head)
		return;

	if(head->value == num)
	{
		nodePtr = head->next;
		head = nodePtr;
	}
	else
	{
		nodePtr = head;
		while(nodePtr!=NULL && nodePtr->value != num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		previousNode->next=nodePtr->next;
	}
}
void displayList()
{
	struct ListNode *nodePtr;
	nodePtr=head;
	printf("\nCurrent List:\n");
	while(nodePtr){
		printf("Value: %d\n",nodePtr->value);
		nodePtr = nodePtr->next;
	}

}

void *deleteRCU(void *param)
{
	struct ListNode *nodePtr,*tempNode;
	pthread_mutex_lock(&lock);
	int pos=((int*)param);
        nodePtr=head;
        pos=pos-1;
        while(nodePtr->next != NULL && count!=pos-1)
        {
               count++;
               nodePtr = nodePtr->next;
        }
        if(count == pos-1)
        {
                //temp->data = data_value;
		tempNode=nodePtr;
		nodePtr=nodePtr->next;
                tempNode->next=nodePtr->next;
        }
        else
        {
                printf("No Such locaion");
        }
  	 printf("This is by Write-Thread\n");
   	displayList();
  pthread_mutex_unlock(&lock);

}
void *displayRCU(void *param)
{
	struct ListNode *nodePtr,*previousNode;
	int pos=0,num=0;
	nodePtr=head;
	pos=(int *)param;
	pthread_mutex_lock(&lock);
	printf("Display Thread\n");
	while(nodePtr!=NULL){
	
    		printf("Value: %d\n",nodePtr->value);
		if(num==pos){
			pthread_mutex_unlock(&lock);
		}
    		num++;
    		nodePtr = nodePtr->next;
  	}
}
