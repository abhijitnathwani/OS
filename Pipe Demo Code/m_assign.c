#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAX 5

int main(){
	int pid,send,rec;
	int status,arr[MAX],arr1[MAX],arr2[MAX];
	int pc[2],cp[2],temp,i,j;
	pipe(pc);
	pipe(cp);

	pid = fork();

		if(pid < 0){
			perror("fork");
			exit(1);
		}
		/* Child Process */
		if(pid == 0){
			dup2(pc[0],0);
			close(pc[1]);

			for(i=0;i<MAX ; i++){
				read(0,&rec,sizeof(rec));
				printf("Child receive = %d\n",rec);
				arr[i] = rec;			
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
			//dup2(cp[1],1);
			//close(cp[0]);
			//write(1,&arr,sizeof(arr));

			//write()
			// printf("After sorting\n");
			// for (i = 0; i <MAX; ++i)
			// {
			// 	printf("%d\t",arr[i] );
			// }
			// printf("\n");

		}else{
			printf("Parent \n");
			dup2(pc[1],1);
			close(pc[0]);
			dup2(cp[0],0);
			close(cp[1]);
						
			
			for(i=0;i<MAX ; i++){
				scanf("%d",&send);
				write(1,&send,sizeof(send));
			}

			
			//wait(&status);
		}
	return 0;
}