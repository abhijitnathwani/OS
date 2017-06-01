#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#include <signal.h>
#define m 100
int main()
{
  char data[m];
 char c[100];
 char buff[1000];
 int pid1=-1,pid=-1;
  int i,socketfd,confd,len;
  struct  sockaddr_in serv_addr;
  socketfd=socket(AF_INET,SOCK_STREAM,0);
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
//  serv_addr.sin_addr.s_addr=INADDR_ANY;
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
  pid=fork();
for (i=0;i<=100;i++)//allow max 3 request
{
   if (i>1)
    {
      pid1=fork();//fork() act as a servlet(in Java)
        if (pid1==0)
        {
          //kill(getppid(),9);

          for(i=0;i<100;i++)
          {
             confd=accept(socketfd,(struct sockaddr*) &serv_addr,&len);
          
            read(confd,data,m);
            printf("child(buffer server)recived file from client is %s\n",data );
            int fp;
            fp=open(data,O_RDONLY);
            read(fp,buff,1000);
            write(confd,buff,1000); 
    
         }
      
        }
    }
    confd=accept(socketfd,(struct sockaddr*) &serv_addr,&len);
    read(confd,data,m);
    printf("recived file from client is %s\n",data );
    int fp;
    fp=open(data,O_RDONLY);
    read(fp,buff,1000);
    write(confd,buff,1000);
   
  
}

  close(socketfd);

}
