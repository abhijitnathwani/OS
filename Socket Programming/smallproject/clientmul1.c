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
pthread_mutex_t m1;
void *runner(void * name);
int main()
{
   
         pthread_t p1[5];
         int n;
         int array[5];
        //param[1] = 456;
        printf("how many file you want to send?\n");
        scanf("%d",&n);
             printf("enter file name\n");
       for (int i = 0; i < n; ++i)
        { 

          scanf("%s",file[i]);
        }

         for (int i = 0; i < n; i++)//for multiple client(hanle multiple client request)
         {
                //printf("i=%d\n",i );
            printf("hello\n");
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
  caddr.sin_port=htons(2001);//port number of server(that handle the client request)
  clen=sizeof(caddr);
  connect(sockfd,(const struct sockaddr*) &caddr,clen);
  strcpy(data,file[i]);//copy the file name into data char_array
  write(sockfd,data,sizeof(data));//write data(our array) into socketdis.
  read(sockfd,datar,sizeof(datar));//read the data from server
  //memset(datar,'0',sizeof(datar));
  printf("Received from server %s\n",datar);
   memset(datar,'0',sizeof(datar));
   pthread_exit(0); 
  //sleep(1); 
    //memset(datar,'0',sizeof(datar));
  close(sockfd);
  //pthread_mutex_unlock(&m1);   
}
