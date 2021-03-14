////////////////////////////////////////////////////////////////////////////////
// Filename: lru.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date:
////////////////////////////////////////////////////////////////////////////////

#include "page_algorithm.h"

int main(int argc, char *argv[]) {
    const int DEFAULT_PAGE_SIZE = 4096;
    const int DEFAULT_MEMORY_SIZE = 1;
    const int BUFF_LEN = 4096;

    clock_t start, end;
    start = clock();
    // double elapsed_time;
    int loop = 1;
    int dq_flag = 0;
    int f_flag = 0;
    int ppn = 0;
    int *tags;
    int sizes[2];
    int max_ppn;
    int temp_ppn;
    // int pages_occupied = 0;
    // int runable_proc = 0;
    long int pos;
    long int clock_tick = 0;
    // long int num_traces = 0;
    // long int page_faults = 0;
    char *filename;
    char buff[BUFF_LEN];
    FILE *file;
    Queue *proc_table;
    Queue *diskQueue;
    DLL_Queue *lru_rq;
    Queue *freelist;
    Stats *stats;
    PageTable *page_table;
    // Entry *new_entry;
    Entry *tmp_entry;
    Page_ets **invrt_Table;
    Page_ets *new_page;
    // Diskdata *disk_dq;
    void *tempNode;

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
    max_ppn = (sizes[1] << 10) / sizes[0];

    // first pass for process information
    proc_table = create_queue();
    stats = init_stat();
    read_pids(file, proc_table);

    // initialize each queue datastructure
    diskQueue = create_queue();
    page_table = create_PT();
    invrt_Table = (Page_ets **)calloc(max_ppn, sizeof(Page_ets *));
    if (invrt_Table == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    lru_rq = create_DLL();
    freelist = create_queue();

    // second pass for memory referrences
    while (1) {
        // check whether the last insturction reached EOF
        if (loop == 0) {
            if (diskQueue->size == 0)
                // disk queue is empty ==> end of tracing!
                break;

            // update stats
            update_pgOcc(stats, (deq_diskTime(diskQueue) - clock_tick) *
                                    page_table->size);
            // set the clock to the disk dequeue time
            clock_tick = deq_diskTime(diskQueue);
        }

        if (check_diskIO(diskQueue, clock_tick)) { // disk IO is done
            dq_flag = 1;
            pos = deq_disk(diskQueue);

            // unblock that PID
            unblockProc(proc_table, tags[0]);

            // increment runable process number
            (*(int *)(proc_table->ptr))++;

            // move the file pointer to that trace line
            fseek(file, pos, SEEK_SET);
        }

        // read a line from the trace file and parse PID and VPN
        loop = read_line(file, buff, &pos);
        tags = parse(buff);

        // check whether the process is blocked or the line has been read
        if (isBlock(proc_table, tags[0]) || isRead(proc_table, tags[0], pos)) {
            // no memory reference for this line
            continue;
        }
        // process is runnable
        clock_tick++;

        // look up tags in t_map (cold miss)
        tmp_entry = lookup(page_table, tags);
        if (dq_flag == 0 && tmp_entry == NULL) {
            // block that PID
            blockProc(proc_table, tags[0], pos, stats);

            // into disk queue
            enq_disk(diskQueue, pos, clock_tick);

            // update stats
            update_pgOcc(stats, page_table->size);
            update_runProc(stats, (*((int *)(proc_table->ptr))));
            continue;
        }

        // not a cold miss
        if (tmp_entry != NULL) { // reference from page table
            updateCurrent(proc_table, tags[0], pos);
            lru_ref(lru_rq, invrt_Table, tmp_entry->ppn);
        } else if (dq_flag == 1) { // tracing disk dequeued line
            // start memory referrence
            if (freelist->head != NULL) {
                temp_ppn = ppn;
                ppn = *(int *)(dequeue(freelist));
                f_flag = 1;
            }
            if (page_table->size == max_ppn) { // no pages left
                // replace algorithm here
                lru_replace(lru_rq, invrt_Table, tags);
            } else { // page mapping able
                // add into the page table and inverted page table
                tempNode = map_in_tree(page_table, tags, ppn);
                new_page = create_page(tags, tempNode);
                invrt_Table[ppn] = new_page;

                // upadate current instuction of PID
                updateCurrent(proc_table, tags[0], pos);

                // add that reference in reference queue to trace
                lru_ref(lru_rq, invrt_Table, ppn);

                if (f_flag == 0) {
                    // it was a new page entry mapping
                    ppn++;
                } else {
                    // using freed page entry
                    ppn = temp_ppn;
                    f_flag = 0;
                }
            }
        }

        // reset the diskQ dq_flag to 0
        dq_flag = 0;

        // check whether it's the last reference of PID
        if (isEnd(proc_table, tags[0], pos)) {
            // decrement runable procoess number
            (*((int *)(proc_table->ptr)))--;

            track_free(freelist, invrt_Table, page_table, tags[0], max_ppn);
        }
        // update page occupied in stats
        update_pgOcc(stats, page_table->size);
        update_runProc(stats, (*((int *)(proc_table->ptr))));
        update_TMR(stats);

        // empty the buff for new line
        memset(buff, 0, sizeof(char) * BUFF_LEN);
    }
    end = clock();
    print_stats(stats, clock_tick, max_ppn, start, end);
    return 0;
}
