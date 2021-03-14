#include "page_algorithm.h"

// void *init_refQ() {
//     DLL_Queue *refQueue = create_DLL();
//     return refQueue;
// }

void trace_ref(DLL_Queue *refQueue, Page_ets **ivrtTable, int ppn) {
    DL_Node *cur = (DL_Node *)(ivrtTable[ppn]->ptr);
    if (cur == NULL) {
        ivrtTable[ppn]->ptr = enq_DLL(refQueue, ppn);
    } else if (refQueue->tail == cur) {
        // this case include when the size is 1
        return;
    } else {
        if (refQueue->head == cur) {
            refQueue->head = cur->next;
            refQueue->head->prv = NULL;
        }
        refQueue->tail->next = cur;
        cur->prv = refQueue->tail;
        cur->next = NULL;
        refQueue->tail = cur;
    }
}

void ref_from_pt(Queue *procTable, Page_ets **ivrtTable, DLL_Queue *refQueue,
                 long int pos, int pid, int ppn) {
    updateCurrent(procTable, pid, pos);
    trace_ref(refQueue, ivrtTable, ppn);
}

void page_replace(DLL_Queue *refQueue, Page_ets **invrtTable, int *tuple) {
    // test
    int ret_ppn = deq_DLL(refQueue);
    printf("(%d,%d) -> (%d, %d)\n", invrtTable[ret_ppn]->tuple[0],
           invrtTable[ret_ppn]->tuple[1], tuple[0], tuple[1]);
    invrtTable[ret_ppn]->tuple[0] = tuple[0];
    invrtTable[ret_ppn]->tuple[1] = tuple[1];

    trace_ref(refQueue, invrtTable, ret_ppn);
}