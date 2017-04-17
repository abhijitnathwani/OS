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
char *buff;
//------------creating FIFO-------------------
//if(mkfifo("my_fifo",S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)==0)
//printf("Fifo created successfully\n");
//-----------created fifo successfully--------

fd=open("my_fifo",O_RDONLY);
read(fd,buff,12);
printf("read from fifo %s\n",buff);
close(fd);

return 0;
}

