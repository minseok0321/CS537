#include "page_algorithm.h"

// void *init_refQ() {
//     Queue *refQueue = create_queue();
//     return refQueue;
// }

void trace_ref(DLL_Queue *refQueue, Page_ets **ivrtTable, int ppn) {
    // test
    // printf("tracing fifo ref!\n");
    // int *ref_ppn = (int *)calloc(1, sizeof(int));
    // if (ref_ppn == NULL) {
    //     fprintf(stderr, "error: memory allocation failed\n");
    //     exit(EXIT_FAILURE);
    // }
    // *ref_ppn = ppn;
    // test
    // printf("referenced ppn: %d\n", *ref_ppn);
    if (ivrtTable[ppn] == NULL) {
        printf("ivrtTable[%d] is null!\n", ppn);
    }
    ivrtTable[ppn]->ptr = enq_DLL(refQueue, ppn);
}

void ref_from_pt(Queue *procTable, __attribute__((unused)) Page_ets **ivrtTable,
                 __attribute__((unused)) DLL_Queue *refQueue, long int pos, int pid,
                 __attribute__((unused)) int ppn) {

    updateCurrent(procTable, pid, pos);
}

void page_replace(DLL_Queue *refQueue, Page_ets **invrtTable, int *tuple) {
    // get the first-referenced page's ppn
    int rep_ppn = deq_DLL(refQueue);

    // // free that reference data
    // free(ref_ppn);

    // change that page to have the new memory reference
    Page_ets *page_ets = invrtTable[rep_ppn];
    //test
    // printf("(%d,%d) -> (%d, %d)\n", page_ets->tuple[0], page_ets->tuple[1], tuple[0], tuple[1]);
    page_ets->tuple[0] = tuple[0];
    page_ets->tuple[1] = tuple[1];

    // change in page table
    // ((Entry *)(*(page_ets->pgTable))) = tuple;

    // trace this new reference to the reference queue
    trace_ref(refQueue, invrtTable, rep_ppn);
}