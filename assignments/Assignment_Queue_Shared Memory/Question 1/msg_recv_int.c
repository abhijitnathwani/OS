#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSZ     128


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
    key_t key;
    message_buf rbuf;
    size_t buf_length ;
    buf_length = sizeof(rbuf.mtext);

    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 234;	

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    
    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(msqid, &rbuf, buf_length, 1,  0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * Print the answer.
     */
    printf("Receive1 data = %d \n", rbuf.mtext);
    exit(0);
}
