////////////////////////////////////////////////////////////////////////////////
// Filename: proc_table.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////
#ifndef PROC_TABLE_H
#define PROC_TABLE_H

#include "input.h"
#include "queue.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
A process struct that stores the info of PID, state(runable or not),
num of contiguous blocks, starting pos, next starting pos, end pos, 
lastly mapped pos (current), and a queue of starting pos of contiguous 
blocks.
*/
typedef struct process {
    int pid;
    int state;
    int cont_blocks;
    long int start;
    long int nextStart;
    long int end;
    long int current;
    Queue *startpoints;
} Process;

Process *createProcess(int pid, long int start);
void read_pids(FILE *file, Queue *procTable);
Process *proc_search(Queue *procTable, int pid);
void updateProcTable(Queue *procTable, int pid, long int pos, int prv_pid);
void updateCurrent(Queue *procTable, int pid, long int pos);
void blockProc(Queue *procTable, int pid, Stats *stat);
void unblockProc(Queue *procTable, int pid);
void terminate(Queue *procTable, int pid, Stats *stat, int num);
int isRunable(Queue *procTable);
Process *earliest_next(Queue *procTable);
int isBlock(Queue *procTable, int pid);
int isRead(Queue *procTable, int pid, long int pos);
int isEnd(Queue *procTable, int pid, long int pos);

#endif
