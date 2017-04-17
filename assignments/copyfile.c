#include<stdio.h>

int main()
{
	FILE *fp1,*fp2;
	char c;
	fp1=fopen("1_1.c","r");
	fp2=fopen("output.txt","w");
	while((c=fgetc(fp1))!=EOF)
	{
		putc(c,fp2);
	}
}
