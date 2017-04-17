#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include <linux/stat.h>

#define FIFO_FILE       "MYFIFO"

int main(void)
{
        FILE *fp,*incomingfile;
        int c;
        char readbuf[80],*buf;

        /* Create the FIFO if it does not exist */
        //umask(0);
        mkfifo(FIFO_FILE, S_IFIFO|0666);

        while(1)
        {	printf("hello at server\n");
                fp = fopen(FIFO_FILE, "r");
                fgets(readbuf, 80, fp);
		if(strlen(readbuf)==0)
		printf("no data received\n");
		else
		{	
                        printf("Received string: %s\n", readbuf);
                        printf("Opening the File %s \n\n", readbuf );
                        incomingfile = fopen(readbuf,"r+");
                        while((c=fgetc(incomingfile))!=EOF)
                        {
                                printf("%c",c );
                        }
                        break;
                	
        	}
	}
        fclose(fp);
        return(0);
}
