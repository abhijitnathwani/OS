#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#define MAX_SIZE 1024

int main()
{
	char data[MAX_SIZE];
	char datar[MAX_SIZE];
	int sockfd,clen,file_size,filesize;
	struct sockaddr_in caddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	caddr.sin_family=AF_INET;
        caddr.sin_addr.s_addr=inet_addr("192.168.55.2");
        caddr.sin_port=htons(3002);
	clen=sizeof(caddr);
	connect(sockfd,(const struct sockaddr*) &caddr,clen);
	printf("Enter data\n");
	scanf("%s",data);
	write(sockfd,data,strlen(data));







	char bytes[10];
	
	recv(sockfd, &file_size, sizeof(int), 0);
	char newfile[30]="new";
	strcat(newfile,data);
	printf("%s\n",newfile);
	printf("Size of read file %d\n",file_size);
	char dataa[MAX_SIZE];
	
	int file_desc,n;
	struct stat	obj;


	FILE *file;


	while((n=read(sockfd,dataa,1024))>=0)
	{
		//if(strcmp(dataa,"-1")==0)
		//	break;
		printf("N: %d\n",n);
		file = fopen(newfile,"a");
		fwrite(dataa, 1,n,file);
		fclose(file);
		stat(newfile,&obj);
		if(obj.st_size == file_size)
			break;

		
		memset(dataa,0,sizeof(dataa));


	}
	
 	printf("Received from server %s\n",datar);
		
		close(sockfd);

	

}
