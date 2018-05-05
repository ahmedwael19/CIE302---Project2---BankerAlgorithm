#ifndef BANKER_H // to prevent multiple includes in the main file
#define BANKER_H

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

extern int available[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
extern int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
extern int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
extern int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* mutex lock */
pthread_mutex_t lock;

/*functions prototypes */
int request_resources(int [], int);
int release_resources(int [], int);
int isSafe(int []);

int release_resources(int release[],int customer_num)
{
    /*use critical section ?*/
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        available[i] += release[i];

    }
}

int request_resources(int request[], int customer_num)
{
    /*A request that leaves the system in
    an unsafe state will be denied. */
    int resource_available=1;
// if request was exceeded its maximum claim:
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        if(request[i]>need[customer_num][i])
        {
            return -1;
        }
    }
    if (pthread_mutex_init(&lock, NULL))
    {
        printf("Mutex initialization failed\n");
        exit(1);
    }

    pthread_mutex_lock(&lock);
    printf("** Start of Critical Secton **\n");

    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        if(request[i]>available[i])
        {
            resource_available = 0;
            printf("** Resource Not Available ** \n"); /* for debugging */
        }
    }

// busy waiting for other processes:
    if(resource_available && isSafe(request))
    {
        printf("** Gochta ** \n"); /* for debugging */

        for(int i=0; i<NUMBER_OF_RESOURCES; i++)
        {
            available[i] -= request[i];
            allocation[customer_num][i] += request[i];
            need[customer_num][i] -= request[i];

            return 1;
        }

    }
    else return -1;

    printf("** End of Critical Secton **\n");
    pthread_mutex_unlock(&lock);
    /* end of critical section */

}



int isSafe(int request[])
{

    /* Let Work and Finish be vectors of length 'NUMBER_OF_RESOURCES' and 'NUMBER_OF_CUSTOMERS' respectively */

    int finish[NUMBER_OF_CUSTOMERS];
    int work[NUMBER_OF_RESOURCES];
    int finish_seq[NUMBER_OF_CUSTOMERS];
    int process_can = 1;
    int count = 0;
    int customer_count = 1;
    int flag = 1;

    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
        work[i] = available[i];

    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
        finish[i] = 0;

    /* if the request is more than what is available, then exit the algoritm from the beginning */
    for(int j=0; j<NUMBER_OF_RESOURCES; j++)
        if(work[j]<request[j])
            return -1;

    /* start of safety algorithm */
    /* request can finish */
    for(int k=0; k<NUMBER_OF_RESOURCES; k++)
    {
        work[k] += allocation[customer_count][k];
    }

    while(count<NUMBER_OF_CUSTOMERS)
    {
        if(finish[customer_count] == 0)
        {
            /* check if the process can be granted the resources */
            for(int j=0; j<NUMBER_OF_RESOURCES; j++)
                if(work[j]>need[customer_count][j])
                    process_can = 0;

            /* process can finish */
            if(process_can)
            {
                for(int k=0; k<NUMBER_OF_RESOURCES; k++)
                    work[k] += allocation[customer_count][k];
                finish[customer_count] = 1;
                finish_seq[count++] = customer_count;
            }
            customer_count = (customer_count + 1) % NUMBER_OF_CUSTOMERS;
        }

        /* for all false states -if they cannot run- then we are in an unsafe state.*/
        // If finish[i] = 1 -for all i-, then the system is in a safe state
        for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
            if(finish[i]==0)
            {
                for(int j=0; j<NUMBER_OF_RESOURCES; j++)
                    if(work[j]>need[customer_count][j])
                        flag = 0;
            }

        if(flag == 1)
        {
            return -1;
        }

    }

    return 1;
}

#endif // BANKER_H
