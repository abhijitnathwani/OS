#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#define m 50

char command[10][10];
pthread_mutex_t m1;
void *runner(void * name);
int main()
{
   
         pthread_t p1[5];
         int n;
         int array[5];
        //param[1] = 456;
        printf("how many command you want to execute?\n");
        scanf("%d",&n);
         printf("enter command\n");
       for (int i = 0; i < n; ++i)
        { 

          scanf("%s",command[i]);
        }

         for (int i = 0; i < n; i++)
         {
                //printf("i=%d\n",i );
            // printf("hello\n");
                pthread_create(&p1[i],NULL,runner,&i);
                  pthread_join(p1[i],NULL);
         
         }
          //close(sockfd);
        return 0;
  }
  
// for (int i=0; i<=4; i++) { 
    
//   }
void *runner(void * name)
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
  caddr.sin_port=htons(2001);
  clen=sizeof(caddr);
  connect(sockfd,(const struct sockaddr*) &caddr,clen);
  strcpy(data,command[i]);
  write(sockfd,data,sizeof(data));
  read(sockfd,datar,sizeof(datar));
  //memset(datar,'0',sizeof(datar));
  printf("Received from server %s\n",datar);
   //memset(datar,'0',sizeof(datar));
   pthread_exit(0); 
  //sleep(1); 
    //memset(datar,'0',sizeof(datar));
  close(sockfd);
  //pthread_mutex_unlock(&m1);   
}
