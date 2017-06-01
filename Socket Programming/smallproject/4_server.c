#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#define m 100
void *readfile();
void *executefile();
pthread_t p1,p2;
  char data[m];
 char c[100];
 char buff[1000];
 char buff1[1000];
  char filecon[1000];
  int i,socketfd,socketfd1,confd,confd1,len,len1;
  struct  sockaddr_in serv_addr;
    struct  sockaddr_in serv_addr1;
int main()
{
//create multiple port for diff. request(file,executable)
  socketfd=socket(AF_INET,SOCK_STREAM,0);
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  socketfd1=socket(AF_INET,SOCK_STREAM,0);
  serv_addr1.sin_family=AF_INET;
  serv_addr1.sin_addr.s_addr=inet_addr("127.0.0.1");
//  serv_addr.sin_addr.s_addr=INADDR_ANY;
  serv_addr.sin_port=htons(2000);
   serv_addr1.sin_port=htons(3000);
  if(bind(socketfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
{
printf("Error\n");
perror("Bind");
}
 if(bind(socketfd1,(struct sockaddr*) &serv_addr1,sizeof(serv_addr1))<0)
{
printf("Error\n");
perror("Bind");
}
  if(listen(socketfd,8)<0)
  {
  printf("Error\n");
  perror("Listen");
  }
  if(listen(socketfd1,8)<0)
  {
  printf("Error\n");
  perror("Listen");
  }
int thread1, thread2;

          thread1=pthread_create(&p1,NULL,readfile,NULL);
            thread2=pthread_create(&p2,NULL,executefile,NULL);
            pthread_join(p1,NULL);
            pthread_join(p2,NULL);
close(socketfd);
  close(socketfd1); 
}

void *readfile()//for file
{
  len=sizeof(serv_addr);
for (int i=0;i<100;i++)
{
  confd=accept(socketfd,(struct sockaddr*) &serv_addr,&len);
  read(confd,data,m);
 printf("recived file from client is %s\n",data );
  int fp;
  fp=open(data,O_RDONLY);
  read(fp,buff,1000);
    write(confd,buff,1000);
}
}
void *executefile()//for executable
{
int j;
for (j=0;j<100;j++)
{

  len1=sizeof(serv_addr1);
  confd1=accept(socketfd1,(struct sockaddr*) &serv_addr1,&len1);
  read(confd1,data,m);
  printf("recived command from client is %s\n",data );

  FILE *fp1;
  fp1=popen(data,"r");
  if(fp1 ==NULL)
  {
    printf("Not successful\n");
    return -1;
  }
  while(fgets(buff1,1000,fp1)!= NULL){//up to this it will execute(it give segmentation fault)
  printf("%s",buff1);
  strcat(filecon,buff1);
}
    printf("hello\n");
    write(confd1,filecon,1000);
   // memset(filecon,0,1000);
    pclose(fp1);

}
}
