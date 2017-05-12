/*
   sched1.c
   Demo sched_yield.
*/
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
int main(){
    int i = 0;
    while(1){
       if(++i == 0) sched_yield();
    }
}