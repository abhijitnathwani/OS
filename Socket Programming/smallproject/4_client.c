#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#define m 50

char file[10][10];
char command[10][10];
pthread_mutex_t m1;
void *runner(void * name);
void *runner1(void *name);
int main()
{
   
         pthread_t p1[5];
         int n,m2;
         int array[5];
        //param[1] = 456;
        printf("how many file you want to send?\n");
        scanf("%d",&n);
             printf("enter file name\n");
       for (int i = 0; i < n; ++i)
        { 

          scanf("%s",file[i]);//scan file name
        }
           printf("how many command you want to execute?\n");
          scanf("%d",&m2);
           printf("enter command\n");
       for (int i = 0; i < m2; ++i)
        { 

          scanf("%s",command[i]);//scan for command(executable file)
        }
         for (int i = 0; i < n; i++)
         {
                //printf("i=%d\n",i );
            //printf("hello\n");
                pthread_create(&p1[i],NULL,runner,&i);
                  pthread_join(p1[i],NULL); 
         }
         for (int i = 0; i < m2; i++)
         {
                //printf("i=%d\n",i );
            //printf("hello\n");
                pthread_create(&p1[i],NULL,runner1,&i);
                  pthread_join(p1[i],NULL); 
         }
          //close(sockfd);
        return 0;
  }
  
// for (int i=0; i<=4; i++) { 
    
//   }
void *runner(void * name)//handle file
{
  //pthread_mutex_lock(&m1);
  int i = *(int*)name;
  char data[m];
  char datar[1000];
  int sockfd,clen;
  struct sockaddr_in caddr;
  memset(data,'0',sizeof(data));
  //memset(datar,'0',sizeof(datar));
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  caddr.sin_family=AF_INET;
   caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  caddr.sin_port=htons(2000);
  clen=sizeof(caddr);
  connect(sockfd,(const struct sockaddr*) &caddr,clen);
  strcpy(data,file[i]);
  write(sockfd,data,sizeof(data));

  read(sockfd,datar,sizeof(datar));

  //memset(datar,'0',sizeof(datar));
  printf("Received from server %s\n",datar);
    memset(datar,'0',sizeof(datar));
   pthread_exit(0); 
  //sleep(1); 
    //memset(datar,'0',sizeof(datar));
  close(sockfd);
  //pthread_mutex_unlock(&m1);   
}
void *runner1(void * name)//handle executable file
{
  //pthread_mutex_lock(&m1);
  int i = *(int*)name;
  char data[m];
  char datar[1000];
  int sockfd,clen;
  struct sockaddr_in caddr;
  memset(data,'0',sizeof(data));
  //memset(datar,'0',sizeof(datar));
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  caddr.sin_family=AF_INET;
   caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  caddr.sin_port=htons(3000);
  clen=sizeof(caddr);
  connect(sockfd,(const struct sockaddr*) &caddr,clen);
  strcpy(data,command[i]);
  write(sockfd,data,sizeof(data));
  read(sockfd,datar,sizeof(datar));
  printf("Received from server %s\n",datar);
  // memset(datar,'0',sizeof(datar));
   pthread_exit(0); 
  close(sockfd);
  //pthread_mutex_unlock(&m1);   
}
