#ifndef BANKER_H // to prevent multiple includes in the main file
#define BANKER_H

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



/* these may be any values >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
/* the available amount of each resource */
extern int available[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
extern int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
extern int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
extern int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* mutex lock */
//pthread_mutex_t lock;
pthread_mutex_t lock;



bool isSafe()
{

    /* Let Work and Finish be vectors of length 'NUMBER_OF_RESOURCES' and 'NUMBER_OF_CUSTOMERS' respectively */

    bool finish[NUMBER_OF_CUSTOMERS];
    int work[NUMBER_OF_RESOURCES];
    //int finish_seq[NUMBER_OF_CUSTOMERS];  ?????
    bool process_can = true;
    int count = 0;
    int customer_count = 1;
    bool flag = true;
    //printf("COUNT : %d \n ",count);
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
        work[i] = available[i];

    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
        finish[i] = false;

    /* if the request is more than what is available, then exit the algoritm from the beginning */
    /* for(int j=0; j<NUMBER_OF_RESOURCES; j++)
         if(work[j]<request[j])
             return false;
    */
    /* start of safety algorithm */
    /* request can finish */
    for(int k=0; k<NUMBER_OF_RESOURCES; k++)
        work[k] += allocation[customer_count][k];

    while(count<NUMBER_OF_CUSTOMERS)
    {
        //printf("COUNT : %d \n ",count);
        if(finish[customer_count] == false)
        {
            /* check if the process can be granted the resources */
            for(int j=0; j<NUMBER_OF_RESOURCES; j++)
                if(need[customer_count][j]>work[j])  //WRONG !
                    process_can = false;

            /* process can finish */
            if(process_can)
            {
                for(int k=0; k<NUMBER_OF_RESOURCES; k++)
                    work[k] += allocation[customer_count][k];
                finish[customer_count] = true;
                count++;
                // finish_seq[count++] = customer_count; ???
                customer_count = (customer_count + 1) % NUMBER_OF_CUSTOMERS; //not sure :/
                break;
            }
printf("STUCK HERE\n");

        }

        /* for all false states -if they cannot run- then we are in an unsafe state.*/
        // If finish[i] = 1 -for all i-, then the system is in a safe state
        for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
            if(finish[i]==false)
            {
                for(int j=0; j<NUMBER_OF_RESOURCES; j++)
                    if(work[j]>need[customer_count][j])
                        flag = false;
                break;
            }

        if(flag == true)
            return false;

    }

    return true;
}


bool release_resources(int release[],int customer_num)
{
    /*add resouces*/
    for(int i=0; i<  NUMBER_OF_RESOURCES; i++)
    {
        //printf("%d\n ",release[i]);
        available[i] += release[i];
    }
    return true;
}

bool request_resources(int request[], int customer_num)
{

//    sleep(1);
    printf("\nCustomer %d is Requesting Resources:\n",customer_num);
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        printf("%d ", request[i]);
    }

    printf("\nAvailable Resources : \n");

    for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        printf("%d ",available[i]);
    }

    printf("\nThe need : \n");
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        printf("%d ",need[customer_num][i]);
    }

    printf("\n");
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        if(request[i] <= need[customer_num][i]) // if the need is more than the request, abort before checking anything else.
        {
            if(request[i]>available[i])
            {
                printf("NOT SAFE with this request (request > available) \n");
                return false;
            }
            else  //taking resources//
            {
 
                if(isSafe())
                {
                    printf("The System is Safe \nResources Granted \n");

		       for(int i=0; i<NUMBER_OF_RESOURCES; i++)
		        {
		            available[i] -= request[i];
		            allocation[customer_num][i] += request[i];
		            need[customer_num][i] -= request[i];
		        }	
		            return true;
		}
                else
                {
                    printf("NOT SAFE ! CAN'T GRANT RESOURCES \n");
                    return false;
                }
            }
        }

        else if(request[i] > need[customer_num][i])
        {
            printf("The request is more than the need. Abort! \n");
            return false;
        }
    }

}



void release_resources_highlevel(int customer_num){
        pthread_mutex_lock(&lock);

        for(int u=0;u<NUMBER_OF_RESOURCES;u++)
        release_resources(maximum[customer_num],customer_num);
        pthread_mutex_unlock(&lock);
	printf(ANSI_COLOR_GREEN "Thread %d finished execution \n" ANSI_COLOR_RESET, customer_num);
}

bool request_resources_highlevel(int request[],int customer_num){
    //CRITICAL SECTION //
    bool released = false;
    pthread_mutex_lock(&lock);
    released=request_resources(request,customer_num);
    pthread_mutex_unlock(&lock);

    return released;
}

#endif // BANKER_H
