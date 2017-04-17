/*
	fifo1.c
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>


#define   FIFO1 "fifo.1"
#define   FIFO2 "fifo.2"

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP |S_IROTH)

#define MAXLINE 4096

int mkfifos(){
  if ((mkfifo (FIFO1, FILE_MODE) < 0) && errno != EEXIST)
  {
      perror ("Can't create Fifo1: ");
  }
  if ((mkfifo (FIFO2, FILE_MODE) < 0) && errno != EEXIST)
  {
      perror ("Can't create Fifo2: ");
//      unlink (FIFO1);
  }
  /* printf("FIFOs made\n"); */
}

int main ()
{
	mkfifos();
}
