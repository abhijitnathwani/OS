#include <stdio.h>
#include <pthread.h>


int iSharedResource;		//shared variable

pthread_mutex_t mutexCount;		//mutex lock reader
pthread_mutex_t mutexResource;		//mutex lock for resource


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
	
	
	
	
	pthread_mutex_lock(&mutexResource);
	printf("READER %d arrived\n", iThreadNum);
	iReaderCount++;
	printf("Reader %d reads = %d\n",iThreadNum, iSharedResource );
	printf("Reader %d entered >>>>>>>>>>>>>>>>> %d\n",iThreadNum, iSharedResource);
	printf("Reader %d exit\n",iThreadNum);
	pthread_mutex_unlock(&mutexResource);	

}


void * setWriter(void *	parm)
{
	int iThreadNum = (int *)parm;
	
		
	

	

	pthread_mutex_lock(&mutexResource);
	printf("\n\t\t\t============================================\n"
			"\t\t\tWRITER %d entered >>> %d\n",iThreadNum, iSharedResource);	
	iSharedResource++;
	printf("\t\t\tWRITER %d write's = %d\n",iThreadNum, iSharedResource );
	printf("\t\t\tWRITER %d exit\n",iThreadNum);
	printf("\t\t\t============================================\n");
	pthread_mutex_unlock(&mutexResource);



}
