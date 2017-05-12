#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>


pthread_t thread; // thread type variable to store the pid of thread
void checkattr(pthread_t);
	
void *thread1()
{
	
	printf("Thread 1 created successfully.\n");
	checkattr(thread); // to check the attributes set, pass the thread as argument
		while(1);
}


int main()
{
	int iRet;
	cpu_set_t cpuset; // variable to store the cpuset
	
	pthread_attr_t attr; // attr type variable

	iRet = pthread_attr_init(&attr);

	CPU_ZERO(&cpuset); // initially clearing the CPU allocation
	CPU_SET(2,&cpuset); // setting the CPU core to 2
	
	
	iRet = pthread_attr_setaffinity_np(&attr,sizeof(cpu_set_t),&cpuset); // applying the CPU affinity to the attr of thread
	


	iRet = pthread_create(&thread,&attr,(void *)thread1,NULL); // creating the thread with the custom attr and thread1 method	

	
	while(1);
	pthread_join(thread,NULL);
	
	
	return 0;
}
void checkattr(pthread_t thread)
{
	pthread_attr_t attrr; // to store the attr of the thread received as argument

	int iRet; // to catch the return value of the the functions
	int iCPU=2; // to catch the cpuset returned by the get affinity function
	
	cpu_set_t cpuset;
	
	iRet = pthread_getattr_np(thread,&attrr); // to get the attr from the thread, and store in to 'attrr' variable

	iRet = pthread_attr_getaffinity_np(&attrr,sizeof(cpu_set_t),&cpuset); // get affinity from the 'attrr'
		
	iRet=CPU_ISSET(iCPU,&cpuset); // convert it to int value

	printf("iRet: %d\n",iRet);
	printf("The current CPU as per attr: %d\n", iCPU);
}
