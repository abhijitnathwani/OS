/*
   sched2.c
   Demo sched_yield.
*/
#define _GNU_SOURCE    
       
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
int main(){
    int i = 0;
    pid_t pid;
    cpu_set_t *mask;

    mask = CPU_ALLOC(3);  // we have a 2 core machhine
    CPU_ZERO(mask);
    CPU_SET(1, mask);     // first CPU is 0, second is 1, etc.
    //CPU_SET(3,mask);    
    pid = getpid();
    if(sched_setaffinity(pid, sizeof(cpu_set_t), mask) == -1)
       perror("SetAffinity");
       
    while(1){
       if(i == 0) sched_yield();
    }
}
