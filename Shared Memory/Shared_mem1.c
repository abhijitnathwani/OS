#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<string.h>
int main()
{
int res,shmid;
char *buff,*s,i;
key_t key = 125;

if((shmid=shmget(key,128,IPC_CREAT|0666))==-1)
{
printf("Fails to get shared memory");
exit(0);
}
printf("shred memory ID = %d\n",shmid);
buff=shmat(shmid,0,0);
printf("%p is assigned\n",buff);

printf("%s read from Shared memory\n",buff);
printf("Writing to shared memory\n");
//buff="hello eitra";
s=buff;

*s='*';
res=shmdt(buff);
printf("shared memory Detached with %d \n",res);
return 0;


}
