////////////////////////////////////////////////////////////////////////////////
// Filename: page_algorithm.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu,
// CS login: doh@best-linux.cs.wisc.edu,
// Date:
////////////////////////////////////////////////////////////////////////////////
#ifndef PAGE_ALGORITHM_H
#define PAGE_ALGORITHM_H

#include "page_algorithm.h"
#include "page_entries.h"
#include "proc_table.h"
#include "queue.h"
#include "queue_DLL.h"
#include "t_map.h"
#include <stdio.h>
#include <stdlib.h>

// void *init_refQ();
void trace_ref(DLL_Queue *refQueue, Page_ets **ivrtTable, int ppn);
void ref_from_pt(Queue *procTable, Page_ets **ivrtTable, DLL_Queue *refQueue,
                 long int pos, int pid, int ppn);
void page_replace(DLL_Queue *refQueue, Page_ets **invrtTable, int *tuple);

// typedef struct ref_data {
//     int ppn;
// } Ref_data;

// void track_free(Queue *freelist, Page_ets **invrt_Table, PageTable *tree,
//                 int PID, int size);
// void fifo_clk_ref(Queue *rq, int ppn);
// void fifo_replace(Queue *rq, Page_ets **invrtTable, int *tuple);
// void lru_ref(DLL_Queue *lru_rq, Page_ets **ivrtTable, int ppn);
// void lru_replace(DLL_Queue *lru_rq, Page_ets **invrtTable, int *tuple);
// void update_hand(Queue *rq);
// void clock_replace(Queue *rq, Page_ets **invrtTable, int *tuple);

#endif
