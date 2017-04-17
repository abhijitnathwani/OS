#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAX 5

int main(){
	int pid,send,rec;
	int status,arr[MAX],arrs[MAX];
	int pc[2],cp[2],temp,i,j;
	pipe(pc);
	pipe(cp);

	printf("1. %d-%d\n", pc[0],pc[1]);
	printf("2. %d-%d\n", cp[0],cp[1]);
	int ar1[5]={1,5,4,3,2};
	pid = fork();

		if(pid < 0){
			perror("fork");
			exit(1);
		}

		if(pid == 0){
			
			
			close(pc[1]);
			wait(status);
			read(pc[0],arr,sizeof(arr));
				printf("Child receive = \n");
				for (int i = 0; i < 5; ++i)
				{
					printf("%d\n", arr[i]);
				}
	
			printf("Before sorting\n");
			for (i = 0; i <MAX; ++i)
			{
				printf("%d\t",arr[i] );
			}
			printf("\n");

			for (j = 0; j < MAX-1; j++)
			{
				for (i = 0; i < MAX-1-j; i++)
				{
					if(arr[i] > arr[i+1]){
						temp = arr[i];
						arr[i] = arr[i+1];
						arr[i+1] = temp;
					}	
				}
			}
			
			
			printf("After sorting\n");
			for (i = 0; i <MAX; ++i)
			{
				printf("%d\t",arr[i] );
				
			}
			printf("\n");
			
			 close(cp[0]);

			write(cp[1],arr,sizeof(arr));
			

		}else{
			printf("Parent \n");
			
			
			close(pc[0]);
			
			
			
				write(pc[1],ar1,sizeof(ar1));
			
			 close(cp[1]);

			printf("parent\n");
			wait(status);
			
			read(cp[0],arrs,sizeof(arrs));
			printf("Parent receive = \n");
			for (int i = 0; i < MAX; ++i)
			{
				printf("%d ", arrs[i]);
			}
			printf("\n");
		}
	return 0;
}
