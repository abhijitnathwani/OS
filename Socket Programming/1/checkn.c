#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd,n;
	int filesize;
	char filename[100];
	char achSendData[100];
	//struct stat obj;
	printf("Enter the file name: ");
	scanf("%s",filename);
	fd=open("e.txt",O_RDONLY);
	while((n=read(fd,filename,10))>0)
	{
		printf("N: %d\n",n);
		memset(achSendData,0,sizeof(achSendData));
	}
	return 0;
}
