/*
   sched3.c
   get scheduling policy
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <string.h>

int main(){
  int policy;
  char pname[20];
  
  policy = sched_getscheduler(0);  // self
  switch(policy){
      case SCHED_OTHER : strcpy(pname, "SCHED_OTHER"); 
                       break;
      case SCHED_BATCH : strcpy(pname, "SCHED_BATCH"); 
                       break;
      case SCHED_IDLE : strcpy(pname, "SCHED_IDLE"); 
                       break;
      case SCHED_FIFO : strcpy(pname, "SCHED_FIFO"); 
                       break;
      case SCHED_RR : strcpy(pname, "SCHED_RR"); 
                       break;
      default: strcpy(pname, "unknown");                 
  }
  printf("This process sched policy is %s\n", pname);
}   