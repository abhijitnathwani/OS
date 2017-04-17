#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
FILE *fp1,*fp2;
fp1=fopen("read_write.c","r");
printf("%p \n",fp1);
fclose(fp1);
fp1=fopen("read_write.c","r");
printf("%p \n",fp1);
fclose(fp1);
return 0;
}
