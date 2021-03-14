////////////////////////////////////////////////////////////////////////////////
// Filename: stats.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////

#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Stat struct that stores start and end real time of the simulator,
num of pages_occupied, runable_procs, traces, and page_faults
*/
typedef struct stats {
    clock_t start, end;
    long int pages_occupied, runable_proc;
    long int num_traces, page_faults;
} Stats;

Stats *init_stat();
void update_pgOcc(Stats *stat, int page_occupied);
void update_runProc(Stats *stat, int runable_proc);
void update_TMR(Stats *stat);
void print_stats(Stats *stat, long int clock, int max_ppn, clock_t start, clock_t end);

#endif
