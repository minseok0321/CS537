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
                 __attribute__((unused)) DLL_Queue *refQueue, long int pos,
                 int pid, __attribute__((unused)) int ppn) {
    updateCurrent(procTable, pid, pos);
}

void update_hand(DLL_Queue *rq) {
    DL_Node *cur = (DL_Node *)(rq->node_ptr);
    if (cur->next == NULL) {
        // set_ptr(rq, rq->head);
        rq->node_ptr = rq->head;
    } else {
        // set_ptr(rq, cur->next);
        rq->node_ptr = cur->next;
    }
}

void page_replace(DLL_Queue *refQueue, Page_ets **invrtTable, int *tuple) {
    int rep_ppn;
    DL_Node *hand;
    Page_ets *page_ets;
    if (refQueue->node_ptr == NULL) {
        // set_ptr(rq, rq->head);
        refQueue->node_ptr = refQueue->head;
    }
    while (1) {
        hand = refQueue->node_ptr;
        rep_ppn = hand->ppn;
        if (invrtTable[rep_ppn]->ref_bit == 0) {
            // change that page to have the new memory reference
            page_ets = invrtTable[rep_ppn];
            page_ets->tuple[0] = tuple[0];
            page_ets->tuple[1] = tuple[1];

            // set the reference bit to 1
            page_ets->ref_bit = 1;
            break;
        }
        invrtTable[rep_ppn]->ref_bit = 0;
        update_hand(refQueue);
    }
}