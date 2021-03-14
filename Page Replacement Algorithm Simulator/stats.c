////////////////////////////////////////////////////////////////////////////////
// Filename: stats.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////

#include "stats.h"

/*
Initializing the stat struct that stores num pages_occupied, runable_proc, 
traces, and page_faults initialized to 0
input:
    Nothing
output:
    returns the stat struct
*/
Stats *init_stat() {
    Stats *stat = (Stats *)calloc(1, sizeof(Stats));
    if (stat == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stat->pages_occupied = stat->runable_proc = 0;
    stat->num_traces = stat->page_faults = 0;
    return stat;
}

/*
Updates the number of pages occupied
input:
    Stats *stat : the stat struct
    int page_occupied : num of page_occupied
output:
    Nothing
*/
void update_pgOcc(Stats *stat, int page_occupied) {
    stat->pages_occupied += page_occupied;
}

/*
Update the number of runable processes
input:
    Stats *stat : the stat struct
    int page_occupied : num of runable process
output:
    Nothing
*/
void update_runProc(Stats *stat, int runable_proc) {
    stat->runable_proc += runable_proc;
}

/*
Update the number of traces by 1 everytime it is called
input:
    Stats *stat : stat struct
output:
    Nothing
*/
void update_TMR(Stats *stat) { stat->num_traces++; }

/*
Print out all the necessary stats
input:
    Stats *stat : stat struct
    long int clock : the clock tick when simulator ends
    int max_ppn : the size of the inverted page table
    clock_t start : starting real time of the simulator
    clock_t end : ending real time of the simulator
*/
void print_stats(Stats *stat, long int clock, int max_ppn, clock_t start,
                 clock_t end) {

    double result = 0;
    max_ppn = (long int)max_ppn;
    result = ((double)(stat->pages_occupied / (double)clock)) / (double)max_ppn;
    // print AMU
    printf("AMU: %lf\n", result);

    // print ARP
    printf("ARP: %lf\n", ((double)stat->runable_proc) / (double)clock);

    // print TMR
    printf("TMR: %ld\n", stat->num_traces);

    // print TPI
    printf("TPI: %ld\n", stat->page_faults);

    // print running time
    printf("Running Time: %ld\n", clock);

    // print real time
    double elapsed_time;
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Real Time: %.2f\n", elapsed_time);
}
