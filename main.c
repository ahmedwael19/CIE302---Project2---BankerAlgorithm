#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "banker.h"
#include <stdbool.h>

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
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        available[i] = atoi(argv[i+1]);
        printf("%d ",available[i]);

        for(int j=0; j<NUMBER_OF_RESOURCES; j++)
        {
            maximum[j][i] = 10;    /* random initializations for maximum allowed requests*/
            need[j][i] = 10;  /*The need should equal the maximum*/
            allocation[j][i]=0;    /*By default the allocation matrix is zero*/
        }
    }


    pthread_t tid[NUMBER_OF_CUSTOMERS]; /* the thread identifiers */

    /* create the thread */
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
        pthread_create(&(tid[i]),NULL,getResources,&i);

    /* now wait for the thread to exit */
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
        pthread_join(tid[i],0);

    pthread_mutex_destroy(&lock);
    return 0;

}

void* getResources(void *arg)
{

    bool released = false;
    int customer_num = *(int *)arg;  //typecasting
    int request_one[] = {6,7,8};     //prototype for a request


    //CRITICAL SECTION //
    pthread_mutex_lock(&lock);
    released=request_resources(request_one,customer_num);
    pthread_mutex_unlock(&lock);
    if(released==true)
    {
        pthread_mutex_lock(&lock);
        release_resources(request_one,customer_num);
        pthread_mutex_unlock(&lock);
        released=false;
    }


    //int request_two[] = {1,2,1};
    //int request_three[] = {2,1,1};


    return 0;
}
