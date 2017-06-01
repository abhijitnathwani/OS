#include <stdio.h>
#include <pthread.h>

void *getIncrement (); // function to be called recursively.
int iValueA = 0;		//variable A
int iValueB = 0;		//variable B

pthread_mutex_t mutexLock;		//mutex lock
pthread_mutexattr_t attr;		//mutex attribute


int main()
{
	int iret1,iret2; // temporary variables to hold the return value for pthread_create
	
	pthread_t tid1,tid2;		//user define threads

	pthread_mutexattr_init(&attr);	//initialization of mutex lock attribute

	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);		//setting mutex attribute
	pthread_mutex_init(&mutexLock, &attr);		//initialization of mutex lock

	iret1=pthread_create(&tid1,NULL,getIncrement,NULL);		//creating thread 1
	iret2=pthread_create(&tid2,NULL,getIncrement,NULL);		//creating thread 2

	pthread_join(tid1,NULL);		//making thread joinable
	pthread_join(tid2,NULL);		//making thread joinable

	printf("A in main : %d \n",iValueA );
	printf("B in main : %d\n", iValueB );

	return 0;
}


void *getIncrement()
{

	pthread_mutex_lock(&mutexLock);
	printf("B in getIncrement function : %d by thread : %lx\n",iValueB++, pthread_self() );
	if(iValueB <= 5){
		getIncrement();	
	}

	pthread_mutex_unlock(&mutexLock);

	printf("B at the end of getIncrement function : %d by thtead : %lx\n",iValueB, pthread_self());

}

/*TYPE OF MUTEX

PTHREAD_MUTEX_NORMAL
This type of mutex does not detect deadlock.
A thread attempting to relock this mutex without first unlocking it will deadlock

PTHREAD_MUTEX_ERRORCHECK
This type of mutex provides error checking.
A thread attempting to relock this mutex without first unlocking it will return with an error.

PTHREAD_MUTEX_RECURSIVE
A thread attempting to relock this mutex without first unlocking it will succeed in locking the mutex.
The relocking deadlock which can occur with mutexes of type PTHREAD_MUTEX_NORMAL
cannot occur with this type of mutex.

PTHREAD_MUTEX_DEFAULT
Attempting to recursively lock a mutex of this type results in undefined behaviour.
Attempting to unlock a mutex of this type which was not locked by the calling thread
results in undefined behaviour.

*/
