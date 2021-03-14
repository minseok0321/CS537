/***********************************************************************
* FILENAME : stat.h
*
* DESCRIPTION :
*       This is the stat header file that declares the function needed to
*       for the statistics of the specific queue including enqueue 
*       and dequeue count plus each of their time.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#ifndef STAT_H
#define STAT_H
#include "queue.h"
#include <stdio.h>
#include <time.h>
#include <semaphore.h>

typedef struct statistics{
    int enQcount;
    int deQcount;
    double enQtime;
    double deQtime;
    sem_t stat_mutex;
}Stat;

Stat *createStatistics();
void update_enQstat(clock_t start, Stat* stat);
void update_deQstat(clock_t start, Stat *stat);
void printStatistics(Stat *stat);

#endif