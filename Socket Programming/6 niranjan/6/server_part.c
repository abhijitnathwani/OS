#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#define MAX_CONTAINT 1000

void *saas();
char achData[MAX_CONTAINT];	//for achData transfer

int iConnectionDis;		// descriptor for connection
pthread_t serverThread;
pthread_mutex_t mutexLock;

int main()
{

	int iIndex;			// index for loop
	int iSocketDis;		// descriptor for socket

	int iLenght;			// length of srtuct sockaddr_in
	struct  sockaddr_in serv_addr;		// structure variable
	int i;
	// making socket using TCP
	iSocketDis=socket(AF_INET,SOCK_STREAM,0);		

	serv_addr.sin_family=AF_INET;		// assigning IP type
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");	// IP address
	serv_addr.sin_port=htons(3002);		// port number

	// binds a socket to a local socket address
	if(bind(iSocketDis,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
	{
		printf("Error\n");
		perror("Bind");
	}

	// makes a socket, a listening socket
	// which will accept 8 new connections
	if(listen(iSocketDis,8)<0)
	{
		printf("Error\n");
		perror("Listen");
	}
	
	iLenght=sizeof(serv_addr);

	// server will serve 100 request
	for (iIndex = 0; iIndex < 100; iIndex++)
	{
		
		// to get a new socket with a new incoming connection
		iConnectionDis = accept(iSocketDis,(struct sockaddr*) &serv_addr,&iLenght);

		if (iConnectionDis < 0)
		{
			printf("connection not accepted\n");
			return 1;
		}
		pthread_create(&serverThread,NULL,saas,NULL);
		pthread_join(serverThread,NULL);
	}
	close(iSocketDis);
}


void *saas()
{

	FILE *fptr;
	char achTemp[1024];
	pthread_mutex_lock(&mutexLock);

	if((read(iConnectionDis,achData,MAX_CONTAINT)) < 0){
		printf("not read from socket\n");
		exit(0);
	}
	printf("\n\tDATA:%s\n",achData);

	fptr = popen(achData,"r");

	memset(achData,0,sizeof(achData));	// removing output of file
	pthread_mutex_unlock(&mutexLock);
}