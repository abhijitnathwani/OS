#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
 * Declare the message structure.
 */

typedef struct msgbuf {
         long    mtype;
         int    mtext;
         } message_buf;

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    size_t buf_length;

    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 234;

(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,\
%#o)\n",
key, msgflg);

    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    else 
     (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);


    /*
     * We'll send message type 1
     */
    
    int ch;
    
    do{
            printf("1. Send Message\n");
            printf("2. Quit\n");
            printf("Enter your choice: \n"); 
            scanf("%d",&ch);
            if(ch==2)
            {
                exit(0);
            }
            else
            {
                    
                    sbuf.mtype = 1;
                    printf("Enter data = \n");
                    scanf("%d",&sbuf.mtext);
                    
                   // (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
                    
                    //(void) strcpy(sbuf.mtext, "Did you get this? 2");
                    
                    
                    //(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
                    
                    //buf_length = strlen(sbuf.mtext) + 1 ;
                    buf_length = sizeof(sbuf.mtext);
                    

                    /*
                     * Send a message.
                     */
                    if (msgsnd(msqid, &sbuf, buf_length, 0) < 0) {
                       printf ("%d, %ld, %d, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
                        perror("msgsnd");
                        exit(1);
                    }

                   else 
                      printf("Message: \"%d\" Sent\n", sbuf.mtext);
            }
    }while(ch!=2);
    exit(0);
}
