#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


int iSharedResource;		//shared variable

sem_t semCount;		//mutex lock reader
sem_t semWriter;		//mutex lock writer


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

	sem_init(&semWriter,0,1);
	sem_init(&semCount,0,1);

	pthread_t threadReadder[MAX_READER];		//reader threads
	pthread_t threadWriter[MAX_WRITER];		//writer threads

	int iIndex;

	//writer creation
	for (iIndex = 0; iIndex < MAX_WRITER; iIndex++)
	{
		pthread_create(&threadWriter[iIndex],NULL,setWriter,(void *) iIndex);
	}

	//reader creation
	for ( iIndex = 0; iIndex < MAX_READER; iIndex++)
	{
		pthread_create(&threadReadder[iIndex],NULL,getReader,(void *) iIndex);
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
	printf("Reader %d entered >>>>>>>>>>>>>>>>> %d\n",iThreadNum, iSharedResource);
	while(iWriterCount != 0);
	sem_wait(&semWriter);
	printf("Reader %d reads = %d\n",iThreadNum, iSharedResource );
	sem_post(&semWriter);
	printf("Reader %d exit\n",iThreadNum);
}


void * setWriter(void *	parm)
{
	int iThreadNum = (int *)parm;
	sem_wait(&semCount);
	printf("WRITER %d arrived\n", iThreadNum);
	iWriterCount++;
	sem_post(&semCount);
	
	sem_wait(&semWriter);
	printf("\n\t\t\t============================================\n"
		"\t\t\tWRITER %d entered >>> %d\n",iThreadNum, iSharedResource);
	iSharedResource++;
	printf("\t\t\tWRITER %d write's = %d\n",iThreadNum, iSharedResource );
	sem_post(&semWriter);

	sem_wait(&semCount);	
	printf("\t\t\tWRITER %d exit\n",iThreadNum);
	--iWriterCount;
	printf("\t\t\t============================================\n");
	sem_post(&semCount);

}
