#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int pid1=-1,pid2=-1,pid3=-1,pid4=-1;
	int ar[100],sum[4],status;
	int flag[4];
	int tmp=0;
	for (int i = 0; i < 100; ++i)
	{
		ar[i]=i;
	}

	pid1=fork();
	if (pid1==0)
	{
		while((wait(&status))!=-1)
		{
		int sum1=0;
		for(int i=0;i<25;i++)
		{
			sum1=sum1+ar[i];
		}
		sum[0]=sum1;
		flag[0]=1;
		printf("sum1=%d\n",sum1 );
		//exit(0);
		}
		exit(0);
		
	}
	if(pid1==0)
	{
		pid2=fork();
		if(pid2==0)
		{
			
			while((wait(&status))!=-1)
			{	
			int sum1=0;
			for(int i=25;i<50;i++)
			{
				sum1=sum1+ar[i];
			}
			sum[1]=sum1;		
			flag[1]=1;
			wait(&status);
			printf("sum2=%d\n",sum1 );
			//exit(0);
			}
			exit(0);
		}

	}
	if(pid2==0)
	{
		pid3=fork();
		if(pid3==0)
		{
			while((wait(&status))!=-1)
			{
				printf("ddd\n");
			int sum1=0;
			for(int i=50;i<75;i++)
			{
				sum1=sum1+ar[i];
			}
			sum[2]=sum1;
			wait(&status);
			printf("sum3=%d\n",sum1 );		
			//exit(0);
			}
			exit(0);
		}
	}
	if(pid3==0)
	{
		pid4=fork();
		if(pid4==0)
		{

			int sum1=0;
			for(int i=75;i<100;i++)
			{
				sum1=sum1+ar[i];
			}
			sum[3]=sum1;
			wait(&status);
			printf("sum4=%d\n",sum1 );		
			exit(1);
		}
		

	}
	
	while((wait(&status))!=-1)
	{
		for(int i=0;i<4;i++)
		{
			printf("----%d\n", sum[i]);
			tmp=tmp+sum[i];
		}	
		//printf("total=%d\n",tmp );
		printf("parent_total=%d\n",tmp);
	}
	
	while(1)
	{
		sleep(1);
	
	};
	return 0;
}