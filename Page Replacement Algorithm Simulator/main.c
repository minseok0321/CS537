////////////////////////////////////////////////////////////////////////////////
// Filename: fifo.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date:
////////////////////////////////////////////////////////////////////////////////

#include "diskQ.h"
#include "freelist.h"
#include "input.h"
#include "page_algorithm.h"
#include "page_entries.h"
#include "stats.h"
#include "t_map.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int DEFAULT_PAGE_SIZE = 4096;
    const int DEFAULT_MEMORY_SIZE = 1;
    // const int BUFF_LEN = 4096;

    clock_t start, end;
    start = clock();
    // double elapsed_time;
    // int loop = 1;
    int dq_flag = 0;
    int f_flag = 0;
    int ppn = 0;
    int tags[2];
    int sizes[2];
    int max_ppn;
    int temp_ppn;
    int runable;
    int free_num;
    // // test
    // int count = 0;
    // int x = 0;
    // int pages_occupied = 0;
    // int runable_proc = 0;
    long int pos;
    long int earl_pos;
    long int clock_tick = 0;
    // long int num_traces = 0;
    // long int page_faults = 0;
    char *filename;
    // char buff[BUFF_LEN] = "";
    FILE *file;
    Queue *proc_table;
    Queue *diskQueue;
    DLL_Queue *refQueue;
    Queue *freelist;
    Stats *stats;
    PageTable *page_table;
    Entry *new_entry;
    Entry *tmp_entry = NULL;
    Page_ets **invrt_Table;
    Page_ets *new_page;
    Process *nextProc;
    Process *tmp_proc;
    void *tmp;

    // set the default sizes
    sizes[0] = DEFAULT_PAGE_SIZE;
    sizes[1] = DEFAULT_MEMORY_SIZE;

    // read command line
    filename = read_arg(argc, argv, sizes);

    // open tracefile
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "error: no such trace file exist\n");
        exit(EXIT_FAILURE);
    }

    // put the max entry's index for max PPN
    // max_ppn = ((long int)(sizes[1] << 20) / sizes[0]);
    max_ppn = 4;

    // test
    // max_ppn = 4;

    // test
    clock_t t1 = clock();

    // test
    printf("first pass...\n");

    // first pass for process information
    proc_table = create_queue();
    stats = init_stat();
    read_pids(file, proc_table);
    runable = proc_table->size;

    // test
    clock_t t2 = clock();

    // test
    printf("read pid time-");
    print_execTime(t1, t2);

    // test
    t1 = clock();

    // initialize each queue datastructure
    diskQueue = create_queue();
    page_table = create_PT();
    invrt_Table = (Page_ets **)calloc(max_ppn, sizeof(Page_ets *));
    if (invrt_Table == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // refQueue = create_queue();
    refQueue = create_DLL();
    freelist = create_queue();

    // initilize the file pointers
    fseek(file, 0, SEEK_SET);
    pos = 0;

    // test
    t2 = clock();
    printf("before going into second loop-");
    print_execTime(t1, t2);

    // second pass for memory referrences
    // test
    t1 = clock();
    // tags = read_line(file, &pos);

    while (1) {
        // count++;
        if (isRunable(proc_table) == 0) { // nothing to run
            // test
            // printf("loop %d: nothing to run\n", count);
            if (diskQueue->size == 0) {
                // END!
                break;
            }
            // update stats
            update_pgOcc(stats, (deq_diskTime(diskQueue) - clock_tick) *
                                    page_table->size);
            // test
            // printf("clock tick to deq time\n");
            clock_tick = deq_diskTime(diskQueue);
        }

        if (check_diskIO(diskQueue, clock_tick)) { // disk IO is done
            dq_flag = 1;
            pos = deq_disk(diskQueue);
            // test
            // printf("disk dqed pos: %d\n", ((int)pos / 4) + 1);

            // // unblock that PID
            // unblockProc(proc_table, tags[0]);

            // // increment runable process number
            // (*(int *)(proc_table->ptr))++;

            // move the file pointer to that trace line
            fseek(file, pos, SEEK_SET);
        }

        // read a line from the trace file and parse PID and VPN
        read_line(file, &pos, tags);

        // test
        if (tags[0] == -1)
            continue;

        if (dq_flag == 1) { // read disk dequeued line
            // unblock that PID
            unblockProc(proc_table, tags[0]);
            // test
            // printf("unblock pid:%d\n", tags[0]);
            runable++;
        }

        // check whether the process is blocked or the line has been read
        if (isBlock(proc_table, tags[0]) || isRead(proc_table, tags[0], pos)) {
            // no memory reference for this line
            // test
            // printf("(%d, %d) is blocked so ignore\n", tags[0], tags[1]);
            nextProc = earliest_next(proc_table);
            // printf("this has tp be 1: %d\n", nextProc->startpoints->size ==
            // 1);
            // test
            // if (x == 2) {
            //     // printf("this is 44?: %ld\n", nextProc->nextStart);
            //     exit(1);
            // }
            // if (nextProc->pid == 3) {
            //     // printf("this is 44?: %ld\n", nextProc->nextStart);
            //     x++;
            // }
            // printf("next proc is [pid:%d]\n", nextProc->pid);
            tmp = dequeue(nextProc->startpoints);
            if (tmp == NULL) {
                earl_pos = nextProc->nextStart;
            } else {
                earl_pos = *((long int *)tmp);
                if (nextProc->pid == 3)
                    // printf("why is it 24?: %ld\n", earl_pos);
                    nextProc->nextStart = earl_pos;
            }
            // earl_pos = *((long int *)dequeue(nextProc->startpoints));
            // test
            // printf("get earl_pos here: %d\n", ((int)earl_pos / 4) + 1);
            // nextProc->nextStart = earl_pos;
            // test
            // printf("after earl_pos lin: %d\n", ((int)earl_pos / 4) + 1);
            fseek(file, earl_pos, SEEK_SET);
            // test
            continue;
        }
        tmp_proc = proc_search(proc_table, tags[0]);
        if (tmp_proc->startpoints->size == tmp_proc->cont_blocks) {
            // deq when it's the first starting point
            // test
            // printf("this is for initial [pid:%d] to size: %d ",
            // tmp_proc->pid,
            //    tmp_proc->startpoints->size - 1);
            dequeue(tmp_proc->startpoints);
            // if (nextProc->startpoints->size != 0)
            //     printf("dequeue [pid:%d] starpoint: %ld\n", nextProc->pid,
            //            *((long int *)dequeue(nextProc->startpoints)));
        }
        // process is runnable
        clock_tick++;
        // printf("clock tick %ld\n", clock_tick);
        // test
        // printf("read: [pid:%d] [vpn:%d]\n", tags[0], tags[1]);
        // printf("p_table size: %d\n", page_table->size);

        // test
        // printf("clock tick(1ns): %ld\n", clock_tick);

        // test
        // printf("\n this line is real referencing\n");

        // ??? * 2
        // pages_occupied += page_table->size;
        // runable_proc++;

        // test
        // printf("start lookup\n");
        // printf("PT size: %d\n", page_table->size);

        // test
        // printf("page_table->root: %d\n", page_table->root);
        // look up tags in t_map (cold miss)
        if (dq_flag == 1) { // disk dequeued
            // new page mapping
            if (page_table->size == max_ppn) { // no pages left
                // test
                // printf("start replaceing for %d: (%d,%d)\n", ((int)pos) / 4,
                //        tags[0], tags[1]);
                page_replace(refQueue, invrt_Table, tags);
            } else {
                // test
                // count++;
                // printf("%dth on [pos:%ld]: new mapping (%d,%d)\n", count,
                // pos,
                //    tags[0], tags[1]);
                if (freelist->head != NULL) { // freed page exist
                    temp_ppn = ppn;
                    ppn = *(int *)(dequeue(freelist));
                    f_flag = 1;
                }
                new_entry = (Entry *)(*map_in_tree(page_table, tags, ppn));
                new_page = create_page(new_entry->tuple);
                invrt_Table[ppn] = new_page;

                // upadate current instuction of PID
                updateCurrent(proc_table, tags[0], pos);

                // add that reference in reference queue to trace
                trace_ref(refQueue, invrt_Table, ppn);

                if (f_flag == 0) {
                    // it was a new page entry mapping
                    ppn++;
                } else {
                    // using freed page entry
                    ppn = temp_ppn;
                    f_flag = 0;
                }
            }
            dq_flag = 0;
            // update_TMR(stats);
            // test
            // printf("%ld-TMR: (line:%d) [PID:%d] [VPN:%d]\n",
            // stats->num_traces,
            //        (int)pos / 4, tags[0], tags[1]);
        } else { // find that PID, VPN in page table
            tmp_entry = lookup(page_table, tags);
            if (tmp_entry == NULL) { // need to map a page
                // test
                // printf("(%d,%d) disk enqueued\n", tags[0], tags[1]);
                blockProc(proc_table, tags[0], stats);
                // printf("[pid:%d] blocked\n", tags[0]);
                runable--;
                // test
                // printf("[PID:%d] [VPN:%d] to disk\n", tags[0], tags[1]);
                enq_disk(diskQueue, pos, clock_tick);

                // update stats here
                update_pgOcc(stats, page_table->size);
                update_runProc(stats, runable);
                continue;
            } else { // page exist in page table
                // test
                // printf("(%d, %d) exist in tree\n", tags[0], tags[1]);
                ref_from_pt(proc_table, invrt_Table, refQueue, pos, tags[0],
                            tmp_entry->ppn);
                // update_TMR(stats);
                // printf("%ld-TMR: (line:%d) [PID:%d] [VPN:%d]\n",
                //        stats->num_traces, (int)pos / 4, tags[0], tags[1]);
            }
        }
        // check whether it's the last reference of PID
        if (isEnd(proc_table, tags[0], pos)) {
            // test
            // printf("[PID:%d] terminated\n", tags[0]);

            free_num = track_free(freelist, refQueue, invrt_Table, page_table,
                                  tags[0], max_ppn);
            terminate(proc_table, tags[0], stats, free_num);
            // test
            // printf("[PID:%d] terminate complete!\n", tags[0]);
            // printf("size is now %d\n", page_table->size);
            runable--;
        }

        // update page occupied in stats
        update_pgOcc(stats, page_table->size);
        update_runProc(stats, runable);
        update_TMR(stats);

        // // empty the buff for new line
        // memset(buff, 0, sizeof(char) * BUFF_LEN);
    }
    // test
    t2 = clock();
    printf("end of 2nd loop-");
    print_execTime(t1, t2);
    // printf("!!!!!%ld\n", stats->pages_occupied);

    end = clock();
    print_stats(stats, clock_tick, max_ppn, start, end);

    return 0;
}
