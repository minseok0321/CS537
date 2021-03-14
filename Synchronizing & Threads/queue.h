/***********************************************************************
* FILENAME : queue.h
*
* DESCRIPTION :
*       This is the queue header file that declares all the functions
*       needed for the queue and statistics, and declaring the queue 
*       struct.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stat.h"

typedef struct queue{
    int head;
    int tail;
    int capacity;
    int enQcount;
    int deQcount;
    int numElements;
    clock_t enQtime;
    clock_t deQtime;
    double time_enQ;
    double time_deQ;
    char **entry;
    sem_t enqueue;
    sem_t dequeue;
    //sem_t mutex;
}Queue;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char *DequeueString(Queue *q);

void PrintQueueStats(Queue *q);

#endif
