/*This is a program to illustrate
2     *the message control, msgctl(),
3     *system call capabilities.
4     */

/*Include necessary header files.*/
#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/types.h>
#include    <sys/ipc.h>
#include    <sys/msg.h>
#include <errno.h>


/*Start of main C language program*/
main()
{
 extern int errno;
 int mode, bytes;
 uid_t uid;
 gid_t gid;
 int rtrn, msqid, command, choice;
 struct msqid_ds *buf;
 
 //buf = & msqid_ds;


 /*Get the msqid, and command.*/
 printf("Enter the msqid = ");
 scanf("%d", &msqid);
 

 /*Check the values.*/
 printf ("\nmsqid =%d, command = %d\n",
     msqid, command);

 rtrn = msgctl(msqid, IPC_STAT, buf);

// time_t         msg_stime;    /* Time of last msgsnd() */
  //  time_t         msg_rtime;    /* Time of last msgrcv() */
//    time_t         msg_ctime;    /* Time of last change */
//    unsigned long  __msg_cbytes; /* Current number of bytes in
                                    /*queue (non-standard) */
//    msgqnum_t      msg_qnum;     /* Current number of messages
                                    /*in queue */
//    msglen_t       msg_qbytes;   /* Maximum number of bytes
                                    /*allowed in queue */
//    pid_t          msg_lspid;    /* PID of last msgsnd() */
//    pid_t          msg_lrpid;    /* PID of last msgrcv() */ 


 printf("Time of last msg snd : %ld\n",buf->msg_stime );
 printf("Time of last msg recv : %ld\n",buf->msg_rtime );
 printf("Current bytes in queue : %ld\n",buf->__msg_cbytes );
 printf("Current messages in queue : %ld\n",buf->msg_qnum );
  printf("Maximum bytes allowed in queue : %ld\n",buf->msg_qbytes );
  printf("PID of last msgsnd() : %d\n", buf->msg_lspid);
  printf("PID of last msgrcv() : %d\n", buf->msg_lrpid);
  printf("Permissions on queue : %ho\n", buf->msg_perm.mode);


/*Perform the following if the call is unsuccessful.*/
if(rtrn == -1)
{
    printf ("\nThe msgctl call failed, error number = %d\n", errno);
}
/*Return the msqid upon successful completion.*/
else
    printf ("\nMsgctl was successful for msqid = %d\n",
        msqid);
exit (0);
}