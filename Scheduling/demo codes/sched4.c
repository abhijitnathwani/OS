/*
   sched4.c
   set and get scheduling policy
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <string.h>
//#include<sys/types.h>
//#include<pthread.h>
void print_policy(int x){
  int policy;
  char pname[20];
  policy = sched_getscheduler(x);  // self
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
  printf("This thread sched policy is %d\n",policy);
}

int main(){
  
  struct sched_param schedparm;
int pid;
pid=getpid();
  schedparm.sched_priority = 0;
  print_policy(pid);
  
  sched_setscheduler(pid, SCHED_BATCH, &schedparm);
  print_policy(pid);
  
  sched_setscheduler(pid, SCHED_IDLE, &schedparm);
  print_policy(pid);  

  schedparm.sched_priority =4;

  sched_setscheduler(pid, SCHED_FIFO, &schedparm);
    print_policy(pid);

  sched_setscheduler(pid, SCHED_RR, &schedparm);
    print_policy(pid);        
}   
