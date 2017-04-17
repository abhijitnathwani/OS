//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main()
{
	char string[]="hello World";
	char string1[13];
	int fd;
	//fd=open("hello.txt",O_WRONLY);
	write(1,string,strlen(string));
	//close(fd);

	//fd=open("hello.txt",O_RDONLY);
	read(0,string1,15);
	printf("string1 = %s \n",string1);
	//close(fd);
	return 0;
}

