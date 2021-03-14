/***********************************************************************
* FILENAME : stat.c
*
* DESCRIPTION :
*       This is the stat module file that defines the function needed to
*       print out the statistics of the specific queue including enqueue 
*       and dequeue count plus each of their time.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include "stat.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

/*
* printStat function
*   - This function defines the function that prints out the statistics of
*     a specific queue (enqueue/dequeue counts and times).
*/
Stat *createStatistics(){
    Stat *stat = (Stat *)malloc(sizeof(Stat));
    if(stat == NULL){
        fprintf(stderr, "Failed to allocate memory for Stat struct.");
        exit(1);
    }
    stat->enQcount = 0;
    stat->deQcount = 0;
    stat->enQtime = 0.0;
    stat->deQtime = 0.0;

    if(sem_init(&stat->stat_mutex,0,1)!=0){
        fprintf(stderr, "Failed to initialize mutex for Stat.");
        exit(1);
    }
    
    return stat;
}

void update_enQstat(clock_t start, Stat *stat){
    clock_t end = clock() - start;
    sem_wait(&stat->stat_mutex);
    stat->enQtime += ((double)end/CLOCKS_PER_SEC);
    stat->enQcount += 1;
    sem_post(&stat->stat_mutex);
}

void update_deQstat(clock_t start, Stat *stat){
    clock_t end = clock() - start;    
    sem_wait(&stat->stat_mutex);
    stat->deQtime += ((double)end/CLOCKS_PER_SEC);
    stat->deQcount += 1;
    sem_post(&stat->stat_mutex);
}

void printStatistics(Stat *stat){
    fprintf(stderr, "Enqueue Count: %d\n", stat->enQcount);
    fprintf(stderr, "Enqueue Time: %d\n", stat->enQtime);
    fprintf(stderr, "Dequeue Count: %d\n", stat->deQcount);
    fprintf(stderr, "Dequeue Time: %d\n", stat->deQtime);
}
