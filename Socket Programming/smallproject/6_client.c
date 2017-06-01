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
    int n,iCount;
    int array[5];
        //param[1] = 456;
    printf("No. of commands you want to run?\n");
    scanf("%d",&n);
    printf("Enter the command: \n");
    for (iCount = 0; iCount < n; ++iCount)
        scanf("%s",command[iCount]);
    

    for (iCount = 0; iCount < n; iCount++)
    {
        pthread_create(&p1[iCount],NULL,runner,&iCount);
        pthread_join(p1[iCount],NULL);
         
    }
    
    return 0;
}
void *runner(void * name)
{
  
    int iCount = *(int*)name;
    char data[m];
    char datar[1000];
    int sockfd,clen;
    struct sockaddr_in caddr;
    memset(data,'0',sizeof(data));

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    caddr.sin_family=AF_INET;
    caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    caddr.sin_port=htons(2001);
    clen=sizeof(caddr);
    
    connect(sockfd,(const struct sockaddr*) &caddr,clen);
    strcpy(data,command[iCount]);
    write(sockfd,data,sizeof(data));
    read(sockfd,datar,sizeof(datar));
    
    printf("Received from server %s\n",datar);
    
    close(sockfd);
    pthread_exit(0); 
  
  
  
}
