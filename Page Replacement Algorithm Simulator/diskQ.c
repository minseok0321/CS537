////////////////////////////////////////////////////////////////////////////////
// Filename: diskQ.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu   
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////
#include "diskQ.h"

/*
Enqueue with the position and deq time for the trace that has encounted 
page fault
input:
    Queue *dq : disk queue
    long int pos: the position of the trace that has met page faults
    long int clock: the ending time for the trace to be in disk queue and wait
                    to be mapped.
output:
    Nothing
*/
void enq_disk(Queue *dq, long int pos, long int clock) {
    const long int DISK_TIME = 2000000;

    // create a new disk data to add in the disk queue
    Diskdata *diskData = (Diskdata *)calloc(1, sizeof(Diskdata));
    if (diskData == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    diskData->pos = pos;
    if (dq->size == 0) {
        //fast forwarding the time
        diskData->endtime = clock + DISK_TIME;
    } else {
        Diskdata *prvData = dq->tail->data;
        //fast forwarding the time
        diskData->endtime = prvData->endtime + DISK_TIME;
    }
    enqueue(dq, diskData);
}

/*
Dequeue the trace from the disk queue and returns its corresponding position
in the trace file.
input:
    Queue *dq : disk queue
output:
    returns the head of the disk queue (first one to have been put into the 
    disk queue) and returns its position in the trace file.
*/
long int deq_disk(Queue *dq) {
    Diskdata *dqData = (Diskdata *)dequeue(dq);
    if (dqData == NULL)
        return 0;
    return dqData->pos;
}

/*
Returns the end time of the trace that is located at the head of the disk queue.
input:
    Queue *dq : disk queue
output:
    returns the ending time for the trace at the head of the disk queue,
    to be used later to check with the current clock tick to dequeue or not.
*/
long int deq_diskTime(Queue *dq) {
    Diskdata *head_data = (Diskdata *)(((Node*)(dq->head))->data);
    return head_data->endtime;
}

/*
Check if the head of the disk queue's endtime matches with the current time 
clock tick.
input:
    Queue *dq : disk queue
    long int clock : current clock tick
output: returns 1 if current clock tick equals the disk queue's head trace's 
        ending time or 0 o/w.
*/
int check_diskIO(Queue *dq, long int clock) {
    if (dq->head != NULL) {
        Diskdata *diskData = dq->head->data;
        return clock == diskData->endtime;
    }
    return 0;
}
