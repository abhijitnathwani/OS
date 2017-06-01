#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#define MAX_CONTAINT 1024
#define MAX_CLIENT 1

void *serverClient(void *ptrFile);
char achFileList[5][10] = {"12.mp3","file2","file1.c","file4.c","file2.c"};
int iLenght;			// length of srtuct sockaddr_in
struct sockaddr_in caddr;		// structure variable
pthread_t clientThread[MAX_CLIENT];
pthread_mutex_t mutexLock;
int iSocketDis;		// descriptor for socket


int main()
{

	int iIndex;			// index for loop

	for (iIndex = 1; iIndex <= MAX_CLIENT; iIndex++)
    {
    	pthread_create(&clientThread[iIndex], NULL, serverClient, (void *) iIndex );
    }

    for (iIndex = 1; iIndex <= MAX_CLIENT; iIndex++)
    {
    	pthread_join(clientThread[iIndex], NULL);
    }

	
	// close(iSocketDis);
	printf("MAIN END\n");
}


void *serverClient(void *clientNum)
{
	char achData[MAX_CONTAINT];		// for file and file containt
	int iNum;
	int iIndex;
	int pid;
	char achFileName[20];
	char preEXE[10] = "./";
	char *achEXE[1];
	FILE *fp;
	pthread_mutex_lock(&mutexLock);
	iNum = (int *)clientNum;

	// making socket using TCP
	iSocketDis=socket(AF_INET,SOCK_STREAM,0);
	
	caddr.sin_family=AF_INET;		// assigning IP type
    caddr.sin_addr.s_addr=inet_addr("192.168.55.8");		// IP address
    caddr.sin_port=htons(3001);		// port number
	
	iLenght=sizeof(caddr);

	strcpy(achData,achFileList[iNum - 1]);

	// connects a socket to a remote socket address
	connect(iSocketDis,(const struct sockaddr*) &caddr,iLenght);

	// write file name on remote socket address
	write(iSocketDis,achData,sizeof(achData));
	printf("Client %d >> %s\n",iNum,achData);

	memset(achFileName,0,sizeof(achFileName));
	strcpy(achFileName,achData);

	pthread_mutex_unlock(&mutexLock);
	
	int count = 0;
	// read file containt from remote socket address
	while(read(iSocketDis,achData,sizeof(achData))){
		// write(1,achData,sizeof(achData));
		if(strcmp(achData,"-1") == 0){
			break;
		}
		fp=fopen("new.mp3","a");
		fwrite(achData,1,sizeof(achData),fp);
	   	printf("count %d\n",++count );
   		memset(achData,0,sizeof(achData));
	   	fclose(fp);

	}
	printf("client end\n");

 	close(iSocketDis);
}
