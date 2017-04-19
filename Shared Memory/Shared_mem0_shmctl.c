#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int res,shmid,ret;
char *buff,*s,i;
key_t key = 125;
struct shmid_ds buf; /* shared memory data structure to 
                             hold results */ 

if((shmid=shmget(key,128,IPC_CREAT | 0666))==-1)
{
printf("Fails to get shared memory");
exit(0);
}
printf("shred memory ID = %d\n",shmid);
buff=shmat(shmid,0,0);
printf("%p is assigned\n",buff);

printf("Writing to shared memory\n");
//buff="hello eitra";
s=buff;
strcpy(s,"hello eitra");
/*for(i='a';i<='z';i++)
{
*s=i;
s++;
}
s='\0';*/
printf("%s read from shared memory\n",buff);

//while(*buff!='*')
//sleep(1);

ret=shmctl(shmid, IPC_STAT, &buf);

printf("Size of Segment: %ld\n",buf.shm_segsz );
 printf("Last Attach Time : %ld\n",buf.shm_atime );
 printf("Last De-Attach Time : %ld\n",buf.shm_dtime );
 printf("Last Change Time : %ld\n",buf.shm_ctime );
 printf("PID of creator : %d\n", buf.shm_cpid);
 printf("PID of last operator : %d\n", buf.shm_lpid);
 printf("No. of attaches : %ld\n", buf.shm_nattch);
 printf("Permissions  : %ho\n", buf.shm_perm.mode);
 /*printf("Current bytes in queue : %ld\n",buf->__msg_cbytes );
 printf("Current messages in queue : %ld\n",buf->msg_qnum );
  printf("Maximum bytes allowed in queue : %ld\n",buf->msg_qbytes );
  printf("PID of last msgsnd() : %d\n", buf->msg_lspid);
  printf("PID of last msgrcv() : %d\n", buf->msg_lrpid);
  printf("Permissions on queue : %ho\n", buf->msg_perm.mode);
*/


res=shmdt(buff);
printf("shared memory Detached with %d \n",res);
return 0;


}
