#include<stdio.h>

int main()
{
	FILE *fp;
	fp=fopen("copyfile.c","r");
	printf("%p",fp);
	while(1);
	fclose(fp);
}
