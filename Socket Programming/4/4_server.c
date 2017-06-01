#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <sys/sendfile.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#define MAX_SIZE 1024

char achData[MAX_SIZE];
char achSendData[MAX_SIZE];
int iCount,iSocketfd,iConfd,iLen,iCharCount,c;
FILE *fp;
pthread_t thread[5];
struct  sockaddr_in serv_addr;
pthread_mutex_t lock;
void *sendd();
int main()
{
	
	iSocketfd=socket(AF_INET,SOCK_STREAM,0);

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("192.168.55.2");
	serv_addr.sin_port=htons(3003);

	if(bind(iSocketfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
	{
		printf("Error\n");
		perror("Bind");
	}
	if(listen(iSocketfd,8)<0)
	{
		printf("Error\n");
		perror("Listen");
	}
	iLen=sizeof(serv_addr);
	for (iCount=0;iCount<100;iCount++)
	{
		iConfd=accept(iSocketfd,(struct sockaddr*) &serv_addr,&iLen);
		pthread_create(&thread[iCount],NULL,sendd,NULL);
		
		
	}
	for (iCount=0;iCount<5;iCount++)
	{
	
		pthread_join(thread[iCount],NULL);
		
		
	}
	
	close(iSocketfd);

}
void *sendd()
{
		int fp,n;
		struct stat	obj;
		int	file_desc,
			file_size;


		
		
		char path[500] = "/media/abhijitnathwani/16642B99642B7B1F/Torrent Downloads/Fifty Shades of Grey (2015)/";
		pthread_mutex_lock(&lock);
		read(iConfd,achData,MAX_SIZE);
				printf("%c",achData[0]);
		stat(achData, &obj);
		printf("\n\nFile request from client:%s\n",achData);
		strcat(path,achData);
		file_desc=open(achData,O_RDONLY);
		file_size = obj.st_size;

		//while(read(fp,achSendData,MAX_SIZE)){
			//write(1,achSendData,MAX_SIZE);
		
		//write(iConfd,file_size,sizeof(int));
		send(iConfd, &file_size, sizeof(int), 0);
		
		memset(achSendData,0,sizeof(achSendData));

		while((n=read(file_desc,achSendData,1024))>0)
		{
			//printf("N: %d\n",n);
			write(iConfd,achSendData,n);
			memset(achSendData,0,sizeof(achSendData));
		}
		//write(iConfd,"-1",2);
		//sendfile(iConfd, file_desc, NULL, file_size);
		
		printf("Written: %d Bytes\n",file_size);
		memset(achData,0,sizeof(achData));
		pthread_mutex_unlock(&lock);
}
