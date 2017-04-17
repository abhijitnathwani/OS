#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include <linux/stat.h>

#define FIFO_FILE       "MYFIFO"

int main(void)
{
        FILE *fp;
int i;
        char readbuf[80];

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
		{	printf("Received string: %s\n", readbuf);
                	fclose(fp);
        	}
	}

        return(0);
}
