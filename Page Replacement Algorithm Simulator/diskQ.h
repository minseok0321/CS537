////////////////////////////////////////////////////////////////////////////////
// Filename: diskQ.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////
#ifndef DISKQ_H
#define DISKQ_H

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*
Each trace in the disk queue has the following members.
    long int pos : position of the trace in the trace file
    long int endtime : the end time of the trace (time to be popped out of the 
                       queue and gets mapped)
*/
typedef struct diskdata {
    long int pos;
    long int endtime;
} Diskdata;

void enq_disk(Queue *dq, long int pos, long int clock);
long int deq_disk(Queue *dq);
long int deq_diskTime(Queue *dq);
int check_diskIO(Queue *dq, long int clock);

#endif
