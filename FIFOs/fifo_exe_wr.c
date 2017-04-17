#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
int main()
{
int fd;
char *buff="hello eitra";
//------------creating FIFO-------------------
if(mkfifo("my_fifo",S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)==0)
printf("Fifo created successfully\n");
//-----------created fifo successfully--------

fd=open("my_fifo",O_WRONLY);
write(fd,buff,strlen(buff));

close(fd);

return 0;
}

