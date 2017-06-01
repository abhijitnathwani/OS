#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<pthread.h>
#define m 1000
char file[][10]={"a.txt","b.txt","c.txt","d.txt","e.txt"};
int sockfd,clen,i;
char data[m],datar[m];
void *sendd(void *);
struct sockaddr_in caddr;
pthread_mutex_t lock;
int main()
{


	pthread_attr_t attr;
        int ret;
        pthread_attr_init(&attr);
        ret=pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	
	
	clen=sizeof(caddr);




	pthread_t p1[5];
	int a[5]={0,1,2,3,4};
        
        
         for ( i = 0; i < 5; i++)
         {
                

                pthread_create(&p1[i],NULL,sendd,&a[i]);
         
         }
         for (int j = 0; j < 5; j++)
         {
                pthread_join(p1[j],NULL);
         }
	//printf("Enter data\n");
	//scanf("%s",data);
	
	close(sockfd);

}
void *sendd(void *name)
{
        
        //sleep(1);
        pthread_mutex_lock(&lock);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	caddr.sin_family=AF_INET;
        caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
        caddr.sin_port=htons(3002);
	connect(sockfd,(const struct sockaddr*) &caddr,clen);
        write(sockfd,(char *)file[*(int *)name],sizeof(name));
	read(sockfd,datar,sizeof(datar));
 	printf("Client %d Received from server %s\n",*(int *)name,datar);
        pthread_mutex_unlock(&lock);
	pthread_exit(0);
}
