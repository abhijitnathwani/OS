#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#define MAX_CONTAINT 1000
#define MAX_CLIENT 10

void *serverClient(void *fp);
int iLenght,iCommands;			// length of srtuct sockaddr_in
struct sockaddr_in caddr;		// structure variable
pthread_t clientThread[MAX_CLIENT];
pthread_mutex_t mutexLock;
int iSockfd;		// descriptor for socket


int main()
{

	int iIndex;			// index for loop
	
	// making socket using TCP
	
	printf("Enter the number of commands you want to run: \n");
	scanf("%d",&iCommands);
	for (iIndex = 1; iIndex <= iCommands; iIndex++)
    {
    	pthread_create(&clientThread[iIndex], NULL, serverClient, (void *) iIndex );
    }

    for (iIndex = 1; iIndex <= iCommands; iIndex++)
    {
    	pthread_join(clientThread[iIndex], NULL);
    }

	
	close(iSockfd);
	printf("MAIN END\n");
}


void *serverClient(void *clientNum)
{
	char achData[MAX_CONTAINT];		// for file and file containt
	int iNum;

	pthread_mutex_lock(&mutexLock);
	iNum = (int *)clientNum;
	iSockfd=socket(AF_INET,SOCK_STREAM,0);
	
	caddr.sin_family=AF_INET;		// assigning IP type
    caddr.sin_addr.s_addr=inet_addr("127.0.0.1");		// IP address
    caddr.sin_port=htons(3002);		// port number
	
	iLenght=sizeof(caddr);

	// connects a socket to a remote socket address
	connect(iSockfd,(const struct sockaddr*) &caddr,iLenght);
	
	printf("Enter the command : ");
	scanf("%s",achData);
	

	// write file name on remote socket address
	if((write(iSockfd,achData,sizeof(achData))) < 0){
		printf("Not writer in socket\n");
		exit(0);	
	}
	printf("Client %d >> %s\n",iNum,achData);

	
	// // read file containt from remote socket address
	// read(iSockfd,achData,sizeof(achData));
 	
 // 	printf("========================="
 // 			" Received %d from server "
 // 			"=====================\n %s\n",iNum,achData);
 	pthread_mutex_unlock(&mutexLock);
 		// close(iSockfd);
}