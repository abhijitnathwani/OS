#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSZ     128


/*
 * Declare the message structure.
 */

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
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
    key = 134;

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
                    printf("Enter msg id: \n");
                    scanf("%d",&sbuf.mtype);
                    //sbuf.mtype = 2;
                    
                    (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
                    
                    (void) strcpy(sbuf.mtext, "Did you get this? 2");
                    //scanf("%d",)
                    
                    (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
                    
                    buf_length = strlen(sbuf.mtext) + 1 ;
                    
                    

                    /*
                     * Send a message.
                     */
                    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
                       printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
                        perror("msgsnd");
                        exit(1);
                    }

                   else 
                      printf("Message: \"%s\" Sent\n", sbuf.mtext);
            }
    }while(ch!=2);
    exit(0);
}
