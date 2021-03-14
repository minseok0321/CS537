#include "freelist.h"

int track_free(Queue *freelist, DLL_Queue *refQueue, Page_ets **invrt_Table,
               PageTable *tree, int PID, int size) {
    // test
    // printf("start freeing...\n");
    int num = 0;
    int *free_ppn;
    // test
    // printf("page table pid order: ");
    for (int i = 0; i < size; i++) {
        if (invrt_Table[i] != NULL && invrt_Table[i]->tuple != NULL &&
            invrt_Table[i]->tuple[0] == PID) {
            // test
            // printf("(ppn: %d, %d, %d) ", i, invrt_Table[i]->tuple[0],
            //        invrt_Table[i]->tuple[1]);
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
            del_node(refQueue, (DL_Node *)(invrt_Table[i]->ptr));
            // test
            print_DL(refQueue);
            // invrt_Table[i]->tuple[0] = -1;
            num++;
            // invrt_Table[i] = NULL;
        }
    }
    return num;
}