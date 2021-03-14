////////////////////////////////////////////////////////////////////////////////
// Filename: page_algorithm.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu,
// CS login: doh@best-linux.cs.wisc.edu,
// Date:
////////////////////////////////////////////////////////////////////////////////

#include "page_algorithm.h"

void track_free(Queue *freelist, Page_ets **invrt_Table, PageTable *tree,
                int PID, int size) {
    int *free_ppn;
    for (int i = 0; i < size; i++) {
        if (invrt_Table[i]->tuple[0] == PID) {
            free_ppn = (int *)calloc(1, sizeof(int));
            if (free_ppn == NULL) {
                fprintf(stderr, "error: memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            *free_ppn = i;
            // Entry entry;
            // entry.tuple = invrt_Table[i]->tuple;
            enqueue(freelist, free_ppn);
            free_page(tree, invrt_Table[i]->tuple);
            // invrt_Table[i] = NULL;
        }
    }
}

// we will !only! call this function when we newly map a page
void fifo_clk_ref(Queue *rq, int ppn) {
    Ref_data *refData = (Ref_data *)calloc(1, sizeof(Ref_data));
    if (refData == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    refData->ppn = ppn;
    enqueue(rq, refData);
}

void fifo_replace(Queue *rq, Page_ets **invrtTable, int *tuple) {
    // get the first-referenced page's ppn
    Ref_data *dq_data = (Ref_data *)dequeue(rq);
    int rep_ppn = dq_data->ppn;

    // free that reference data
    free(dq_data);

    // change that page to have the new memory reference
    Page_ets *page_ets = invrtTable[rep_ppn];
    free(page_ets->tuple);
    page_ets->tuple = tuple;

    // change in page table
    ((Entry *)(page_ets->pgTable))->tuple = tuple;

    // trace this new reference to the reference queue
    fifo_clk_ref(rq, rep_ppn);
}

void lru_ref(DLL_Queue *lru_rq, Page_ets **ivrtTable, int ppn) {
    DL_Node *cur = (DL_Node *)ivrtTable[ppn]->ptr;
    if (cur == NULL) {
        enq_DLL(lru_rq, ivrtTable, ppn);
    } else if (lru_rq->tail == cur) {
        // this case include when the size is 1
        return;
    } else {
        if (lru_rq->head == cur) {
            lru_rq->head = cur->next;
            lru_rq->head->prv = NULL;
        }
        lru_rq->tail->next = cur;
        cur->prv = lru_rq->tail;
        cur->next = NULL;
        lru_rq->tail = cur;
    }
}

void lru_replace(DLL_Queue *lru_rq, Page_ets **invrtTable, int *tuple) {
    int ret_ppn = deq_DLL(lru_rq);
    free(invrtTable[ret_ppn]->tuple);
    invrtTable[ret_ppn]->tuple = tuple;
    ((Entry *)(invrtTable[ret_ppn]->pgTable))->tuple = tuple;

    lru_ref(lru_rq, invrtTable, ret_ppn);
}

void update_hand(Queue *rq) {
    Node *cur = (Node *)(rq->ptr);
    if (cur->next == NULL) {
        set_ptr(rq, rq->head);
    } else {
        set_ptr(rq, cur->next);
    }
}

void clock_replace(Queue *rq, Page_ets **invrtTable, int *tuple) {
    int rep_ppn;
    Node *hand;
    Page_ets *page_ets;
    if (rq->ptr == NULL) {
        set_ptr(rq, rq->head);
    }
    while (1) {
        hand = rq->ptr;
        rep_ppn = ((Ref_data *)hand->data)->ppn;
        if (invrtTable[rep_ppn]->ref_bit == 0) {
            // change that page to have the new memory reference
            page_ets = invrtTable[rep_ppn];
            free(page_ets->tuple);
            page_ets->tuple = tuple;

            // change in page table
            ((Entry *)(page_ets->pgTable))->tuple = tuple;

            // set the reference bit to 1
            page_ets->ref_bit = 1;
            break;
        }
        invrtTable[rep_ppn]->ref_bit = 0;
        update_hand(rq);
    }
}