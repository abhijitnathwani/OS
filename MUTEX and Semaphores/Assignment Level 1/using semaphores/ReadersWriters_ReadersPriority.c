#include <stdio.h>
#include <pthread.h>
#include<semaphore.h>


int iSharedResource;		//shared variable

sem_t mutexCount;		//mutex lock reader
sem_t mutexResource;		//mutex lock for resource


void * getReader(void *);		//reader function
void * setWriter(void *);		//writer function

int iReaderCount; //how many reader read the iSharedResource
int iWriterCount; //how many writer waiting for iSharedResource

int main()
{
	int MAX_WRITER;
	int MAX_READER;
	printf("Enter Read = ");
	scanf("%d",&MAX_READER);
	printf("Enter Writer = ");
	scanf("%d",&MAX_WRITER);

	iReaderCount = 0;
	iSharedResource = 25;
	
	sem_init(&mutexCount,0,1);
	sem_init(&mutexResource,0,1);

	pthread_t threadReadder[MAX_READER];		//reader threads
	pthread_t threadWriter[MAX_WRITER];		//writer threads
	int iIndex;

	

	//reader creation
	for ( iIndex = 0; iIndex < MAX_READER; iIndex++)
	{
		pthread_create(&threadReadder[iIndex],NULL,getReader,(void *) iIndex);
	}
	//writer creation
	for (iIndex = 0; iIndex < MAX_WRITER; iIndex++)
	{
		pthread_create(&threadWriter[iIndex],NULL,setWriter,(void *) iIndex);
	}
	

	//making reader thread joinable
	for (iIndex = 0; iIndex < MAX_READER; iIndex++)
	{
		pthread_join(threadReadder[iIndex],NULL);
	}
	//making writer thread joinable
	for (iIndex = 0; iIndex < MAX_WRITER; iIndex++)
	{
		pthread_join(threadWriter[iIndex],NULL);
	}

	printf("All threads terminated\n");
	return 0;
}

void * getReader(void * parm)
{
	int iThreadNum = (int *)parm;		//get reader's thread number
	// printf("Reader %d entered >>>>>>>>>>>>>>>>> %d\n",iThreadNum, iSharedResource);
	

	sem_wait(&mutexCount);
///	pthread_mutex_lock(&mutexCount);
	printf("READER %d arrived\n", iThreadNum);
	iReaderCount++;
	if(iReaderCount==1)
	{
		sem_wait(&mutexResource);
//		pthread_mutex_lock(&mutexResource);
		printf("Reader %d reads = %d\n",iThreadNum, iSharedResource );
	}
	sem_post(&mutexCount);
//	pthread_mutex_unlock(&mutexCount);
	

	printf("Reader %d entered >>>>>>>>>>>>>>>>> %d\n",iThreadNum, iSharedResource);
	
	
	
	
	sem_wait(&mutexCount);
//	pthread_mutex_lock(&mutexCount);
	--iReaderCount;
	printf("Reader %d exit\n",iThreadNum);


	if(iReaderCount==0)
	{
		sem_post(&mutexResource);		
//		pthread_mutex_unlock(&mutexResource);	
	}
	sem_post(&mutexCount);
//	pthread_mutex_unlock(&mutexCount);
}


void * setWriter(void *	parm)
{
	int iThreadNum = (int *)parm;
	
	//while(iReaderCount != 0);
	printf("\n\t\t\t============================================\n"
			"\t\t\tWRITER %d entered >>> %d\n",iThreadNum, iSharedResource);
	do
	{
		sem_wait(&mutexCount);
//		pthread_mutex_lock(&mutexCount);
		if(iReaderCount!=0)
		{
				
			sem_post(&mutexCount);		
//			pthread_mutex_unlock(&mutexCount);
		}
		else
			break;
	}while(1);
	//else
	{
	
	

	
	sem_wait(&mutexResource);
//	pthread_mutex_lock(&mutexResource);	
	iSharedResource++;
	printf("\t\t\tWRITER %d write's = %d\n",iThreadNum, iSharedResource );
	printf("\t\t\tWRITER %d exit\n",iThreadNum);
	--iWriterCount;
	printf("\t\t\t============================================\n");
	sem_post(&mutexResource);
	sem_post(&mutexCount);
//	pthread_mutex_unlock(&mutexResource);
//	pthread_mutex_unlock(&mutexCount);
	}

}
