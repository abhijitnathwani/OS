#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<fcntl.h>
#define MAX_SIZE 65535

int main()
{
	char data[MAX_SIZE];
	char datar[MAX_SIZE];
	int sockfd,clen,file_size;
	struct sockaddr_in caddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	caddr.sin_family=AF_INET;
        caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
        caddr.sin_port=htons(3003);
	clen=sizeof(caddr);
	connect(sockfd,(const struct sockaddr*) &caddr,clen);
	printf("Enter data\n");
	scanf("%s",data);
	write(sockfd,data,strlen(data));







	char bytes[10];
	
	recv(sockfd, &file_size, sizeof(int), 0);
	printf("Size of read file %d\n",file_size);
	char *dataa;
	int file_desc;
	file_desc = open(data, O_CREAT | O_EXCL | O_WRONLY, 0666);
	
	//recv(sockfd, dataa, file_size, 0);
	
	read(sockfd,dataa,file_size);
	write(file_desc, dataa, file_size);
	close(file_desc);
	
	//FILE *fp = fopen("hello.txt","w+");
	//fprintf(fp,"%s",datar);
 	printf("Received from server %s\n",datar);
		
		close(sockfd);

	

}
