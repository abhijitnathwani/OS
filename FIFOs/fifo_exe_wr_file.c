#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define MAX 1000
int main()
{
int fd,num,c,i=0;
FILE *fp;
char buff[MAX];//="hello eitra";
//------------creating FIFO-------------------
if(mkfifo("my_fifo",S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)==0)
printf("Fifo created successfully\n");
//-----------created fifo successfully--------

fd=open("my_fifo",O_WRONLY);
fp=fopen("data.txt","r");

while((c=fgetc(fp))!=EOF)
	buff[i++]=c;

if((num=write(fd,buff,strlen(buff))) == -1)
		perror("write");
else
		printf("Wrote %d bytes\n",num);
fclose(fp);

return 0;
}

