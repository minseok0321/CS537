/***********************************************************************
* FILENAME : queue.c
*
* DESCRIPTION :
*       This is the queue source file that defines all the functions
*       needed for the queue and statistics, and initializes members in 
*       queue struct. 
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include "queue.h"

/*
* CreateStringQueue function
*   - This function creates the queue, initializes all the members in the queue *     struct and semaphores, and returns the pointer to queue.
*/
Queue *CreateStringQueue(int size){
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if(q == NULL){
        fprintf(stderr, "Failed to allocate memory for queue struct on heap.");
        exit(1);
    }
    //creating specific number of buffers that can each contain a line of texts
    q->entry = (char**)malloc(sizeof(char*) * size);
    if(q->entry == NULL){
        fprintf(stderr, "Failed to allocate memory for queue of entries");
        exit(1);
    }
    //initializing the members of queue struct
    q->capacity = size;
    q->head = 0;
    q->tail = 0;
    q->numElements = 0;
    q->enQcount = 0;
    q->deQcount = 0;
    q->time_enQ = 0.0;
    q->time_deQ = 0.0;    

    if(sem_init(&q->enqueue, 0, size) != 0){
        fprintf(stderr, "Failed to initialize the semaphore for enqueue.");
        exit(1);
    }
    if(sem_init(&q->dequeue, 0, 0) != 0){
        fprintf(stderr, "Failed to initialize the semaphore for dequeue.");
        exit(1);
    }

    return q;                            
}

/*
* EnqueueString function
*   - This function is designed to allow enqueuing a line of texts to the      *     queue. Semaphores are used to prevent dequeuing from empty queue or       *     queuing to full queue.
*/
void EnqueueString(Queue *q, char *string){
    //starting the timer for the start of enqueuing
    q->enQtime = clock();
    sem_wait(&q->enqueue);
    //sem_wait(&q->mutex);
    //inserting a line of texts to buffer
    q->entry[q->tail] = string;
    //updating the tail as things get enqueued
    q->tail = (q->tail + 1) % q->capacity;
    q->enQcount += 1;
    q->numElements += 1;
    //sem_post(&q->mutex);
    sem_post(&q->dequeue);
    //ending the timer for enqueuing
    q->enQtime = clock() - q->enQtime;
    //accumulating the time used for enqueuing
    q->time_enQ += ((double)q->enQtime)/CLOCKS_PER_SEC;
}

/*
* DequeueString function
*   - This function is designed to allow dequeuing a line of texts from the   *     queue. Semaphores are used to prevent dequeuing from empty queue or       *     queuing to full queue. Returns the dequeued line of texts.
*/                                
char* DequeueString(Queue *q){
    q->deQtime = clock();
    sem_wait(&q->dequeue);
    //sem_wait(&q->mutex);
    char* string = q->entry[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->deQcount += 1;
    q->numElements -= 1;
    //sem_post(&q->mutex);
    sem_post(&q->enqueue);
    q->deQtime = clock() - q->deQtime;
    q->time_deQ += ((double)q->deQtime)/CLOCKS_PER_SEC;
    return string;
}

/*
* PrintQueueStats function
*   - This function is designed to pass the updated queue to the printStat     *     function that is in stat.c file that prints out the statistics of the    *     passed in queue.
*/                                                                
void PrintQueueStats(Queue *q){
    printStat(q);
}