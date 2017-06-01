#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_SIZE 1024

int main()
{
	char data[MAX_SIZE];
	char achRecvData[MAX_SIZE];
	char *achEXE[1];
	int sockfd,clen,iFileSize;
	struct sockaddr_in caddr;
	long n,percent,old = 0;
	
	struct stat	obj;


	FILE *file;

	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	caddr.sin_family=AF_INET;
    caddr.sin_addr.s_addr=inet_addr("192.168.55.2");
    caddr.sin_port=htons(3003);
	clen=sizeof(caddr);
	
	connect(sockfd,(const struct sockaddr*) &caddr,clen);
	printf("Enter data\n");
	scanf("%s",data);
	
	write(sockfd,data,strlen(data)); // write the file name requested by the client to the server 

	
	recv(sockfd, &iFileSize, sizeof(int), 0); // recv the file size sent from server on the client side.
	
	char newfile[30]="new";
	char achChange[20] = "chmod +x ";
	char achPre[20] = "./";
	strcat(newfile,data); 
	
	printf("%s\n",newfile);
	printf("Size of read file %d\n",iFileSize);
	
	
	

	while((n=read(sockfd,achRecvData,1024))>=0)
	{
		file = fopen(newfile,"a");
		fwrite(achRecvData, 1,n,file);
		fclose(file);
		stat(newfile,&obj);
		
   		percent = (obj.st_size * 100)/ iFileSize;

   		if(old<percent){
   			
   			printf("Download %ld %%\n",percent);
   			old = percent;	
   		}
		if(obj.st_size == iFileSize)
			break;

		memset(achRecvData,0,sizeof(achRecvData));
	}

	strcat(achChange,newfile);
	popen(achChange,"r"); // to change the permission of the received file to executable.

	strcat(achPre,newfile);
	printf("exe %s\n",achPre );
	achEXE[0] = achPre;
	achEXE[1] = NULL;
	sleep(1);
	system(achPre);
	printf("Received from server\n");

 
		
	close(sockfd);

	

}
