#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "banker.h"

/* these may be any values >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* mutex lock */
//pthread_mutex_t lock;

void* getResources(void *arg);

int main(int argc, char *argv[])
{

    if (argc != NUMBER_OF_RESOURCES+1)
    {
        fprintf(stderr,"usage: a.out <# of src 1> <# of src 2> <# of src 3>\n");
        exit(1);
    }

    for(int i=1; i<argc; i++)
        if(atoi(argv[i]) < 0)
        {
            fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[i]));
            exit(1);
        }


    /*setting up the available vector */
    printf("Avaiable \n");
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        available[i] = atoi(argv[i+1]);
        printf("%d  ",available[i]);
    }

    /* random initializations for maximum allowed requests*/
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        for(int j=0; j<NUMBER_OF_RESOURCES; j++)
        {
            maximum[i][j] = 3;
        }
    }
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        for(int j=0; j<NUMBER_OF_RESOURCES; j++)
        {
            need[i][j] = 3;
        }
    }

    pthread_t tid[NUMBER_OF_CUSTOMERS]; /* the thread identifiers */

    /* create the thread */
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        pthread_create(&(tid[i]),NULL,getResources,&i); //problem is herer//
    }
    /* now wait for the thread to exit */
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
        pthread_join(tid[i],NULL);

    pthread_mutex_destroy(&lock);
    return 0;

}

void* getResources(void *arg)
{
	
    int finished = 1;
    int customer_num = *(int *)arg;

    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        if(need[customer_num][i] != 0)
	{
            finished=0;
    	}
     }
    /* request some resoureces */
    /* simulate a process that divides its need on multiple requests */
    /* overall requests = {3,3,3} */
    int request_one[] = {1,1,2};
    int request_two[] = {1,2,1};
    int request_three[] = {2,1,1};


    while(!finished)
    {
        request_resources(request_one, customer_num);
        request_resources(request_two, customer_num);
        request_resources(request_three, customer_num);
    }
    /* thread code should be run here */
    printf("Process has granted all required resources ..");

    /* if granted then release the finished threads */
    if(!release_resources(allocation[customer_num],customer_num))
        printf("Releasing resources for process %d was not successful",customer_num);

    printf("Process %d has finished execution",customer_num);

    return NULL;
}
