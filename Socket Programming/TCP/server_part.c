#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define m 100
int main()
{
	char data[m];
	int i,socketfd,confd,len;
	struct  sockaddr_in serv_addr;
	socketfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
//	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(3000);
	if(bind(socketfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
{
printf("Error\n");
perror("Bind");
}
	if(listen(socketfd,8)<0)
	{
	printf("Error\n");
	perror("Listen");
	}
	len=sizeof(serv_addr);
for (i=0;i<100;i++)
{
	confd=accept(socketfd,(struct sockaddr*) &serv_addr,&len);
	read(confd,data,m);
	write(confd,data,m);
	printf("\n\tDATA:%s\n",data);
}
	close(socketfd);

}
