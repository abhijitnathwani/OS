#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/types.h>
#include    <sys/ipc.h>
#include    <sys/msg.h>
#include <errno.h>
#include <unistd.h>

typedef struct msgbuf{
	long mtype;
	int data;
}message_buf;

int processidof3=0;
int main()
{
	int pid1=-1,pid2=-1,pid3=-1,pid4=-1;

	int msqid,ret;
	key_t key;
        
	message_buf rbuf;
        
	size_t buf_length;
	int rtrn;
    struct msqid_ds buf;
	key = 121;

	if((msqid=msgget(key,IPC_CREAT | 0666))<0)
	{
		perror("msgget");
		exit(1);
	}
	((pid1=fork()) && (pid2=fork()) && (pid3=fork()) && (pid4=fork()));
	if(pid1==0)
	{
		message_buf sbuf;
		sbuf.mtype = 1;
		sbuf.data = 21;
		//msgsnd(msqid,&sbuf,sizeof(sbuf.data),IPC_NOWAIT);

	}
	else if(pid2==0)
	{
		message_buf sbuf;
		sbuf.mtype = 1;
		sbuf.data = 22;
		//msgsnd(msqid,&sbuf,sizeof(sbuf.data),IPC_NOWAIT);
	}
	else if(pid3==0)
	{
		processidof3=getpid();
		message_buf sbuf;
		sbuf.mtype = 2;
		sbuf.data = 23;
		msgsnd(msqid,&sbuf,sizeof(sbuf.data),IPC_NOWAIT);
		printf("pid3: %d\n", processidof3 );
	}
	else if(pid4==0)
	{
		message_buf sbuf;
		sbuf.mtype = 2;
		sbuf.data = 24;
		//msgsnd(msqid,&sbuf,sizeof(sbuf.data),IPC_NOWAIT);
	}
	else
	{
		
		printf("msqid: %d\n", msqid);
		rtrn = msgctl(msqid, IPC_STAT, &buf);
		//while(1){
		//if(buf.msg_lspid == pid3)
		// //{
		// 	rtrn = msgctl(msqid, IPC_STAT, &buf);
		// 	if(buf.msg_lspid == processidof3)
		//     {
		//     	printf("pid3: %d,%d\n", processidof3,pid3 );
		// 		printf("last pid: %d\n", buf.msg_lspid);
		// 		msgrcv(msqid, &rbuf, sizeof(rbuf.data), 2, 0 );
		// 		printf("Data: %d from Process: %d\n",rbuf.data, processidof3 );
		// 	}
		//}
		//}
		sleep(2);
		do
		{
			printf("pid3: %d,\n", pid3 );
		//if((pid3==processidof3)) 
		{
			rtrn = msgctl(msqid, MSG_STAT, &buf);
			printf("%d\n",buf.msg_lspid );
			if(buf.msg_lspid == pid3)
			{
				ret = msgrcv(msqid, &rbuf, sizeof(rbuf.data), 2, 0 );
				printf("sjlkjsljdData: %d from Process: %d\n",rbuf.data, processidof3 );
			}
			sleep(2);
    	}
    	//else
    	{

        	// perror("msgrcv");
        	// exit(1);
    	}
    }while(1);
    }
	
	
	
}
