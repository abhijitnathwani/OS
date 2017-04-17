#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
int fd,i=0;
char buff[1000];
//------------creating FIFO-------------------
//if(mkfifo("my_fifo",S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)==0)
//printf("Fifo created successfully\n");
//-----------created fifo successfully--------

fd=open("my_fifo",O_RDONLY);
read(fd,buff,40);
printf("read from fifo :\n");
for(i=0;buff[i]!='\0';i++)
	printf("%c", buff[i]);
close(fd);

return 0;
}

