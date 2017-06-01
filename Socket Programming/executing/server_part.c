#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#define MAX_SIZE 1000

char achData[MAX_SIZE],achSendData[MAX_SIZE];
int iCount,iSocketfd,iConfd,iLen,iCharCount,c;
FILE *fp;
pthread_t thread[5];
struct  sockaddr_in serv_addr;
pthread_mutex_t lock;
void *sendd();
int main()
{
	
	iSocketfd=socket(AF_INET,SOCK_STREAM,0);

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(3001);

	if(bind(iSocketfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
	{
		printf("Error\n");
		perror("Bind");
	}
	if(listen(iSocketfd,8)<0)
	{
		printf("Error\n");
		perror("Listen");
	}
	iLen=sizeof(serv_addr);
	for (iCount=0;iCount<5;iCount++)
	{
		iConfd=accept(iSocketfd,(struct sockaddr*) &serv_addr,&iLen);
		pthread_create(&thread[iCount],NULL,sendd,NULL);
		
		
	}
	for (iCount=0;iCount<5;iCount++)
	{
	
		pthread_join(thread[iCount],NULL);
		
		
	}
	
	close(iSocketfd);

}
void *sendd()
{
		int fp;
		pthread_mutex_lock(&lock);
		read(iConfd,achData,MAX_SIZE);
		printf("\n\nFile request from client:%s\n",achData);
		fp=open(achData,O_RDONLY);
		read(fp,achSendData,MAX_SIZE);
		write(iConfd,achSendData,MAX_SIZE);
		pthread_mutex_unlock(&lock);
}
