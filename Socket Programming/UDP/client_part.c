#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#define m 100

int main()
{
	char data[m],datar[m];
	int sockfd,clen;
	struct sockaddr_in caddr;

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	caddr.sin_family=AF_INET;
        caddr.sin_addr.s_addr=inet_addr("192.168.55.12");
        caddr.sin_port=htons(3000);
	clen=sizeof(caddr);
	//connect(sockfd,(const struct sockaddr*) &caddr,clen);
	printf("Enter data\n");
	scanf("%s",data);
	sendto(sockfd,data,sizeof(data),0,(const struct sockaddr*) &caddr,clen);
	//write(sockfd,data,sizeof(data));
	// read(sockfd,datar,sizeof(data));
 // 	printf("Received from server %s\n",datar);
	close(sockfd);

}
