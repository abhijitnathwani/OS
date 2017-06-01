#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#define m 100
int main()
{
  char data[m];
 char c[100];
 char filecon[1000];
 char buff[1000];
  int i,socketfd,confd,len;
  struct  sockaddr_in serv_addr;
  socketfd=socket(AF_INET,SOCK_STREAM,0);
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
//  serv_addr.sin_addr.s_addr=INADDR_ANY;
  serv_addr.sin_port=htons(2001);
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
printf("recived file from client is %s\n",data );
//system(data);
FILE *fp;
fp=popen(data,"r");//popen read the executable 
while(fgets(buff,sizeof(buff)-1,fp)!=NULL){//store the executable o/p in buff
printf("%s",buff);
strcat(filecon,buff);//concate buff(contain last line of file) in filecon array
}
//strcpy(buff,system(data));
 // read(fp,buff,1000);
    write(confd,filecon,1000);
pclose(fp);
}
  close(socketfd);

}
