#include "queue_DLL.h"

DLL_Queue *create_DLL() {
    DLL_Queue *dll = (DLL_Queue *)calloc(1, sizeof(DLL_Queue));
    if (dll == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->node_ptr = NULL;
    dll->size = 0;
    return dll;
}

DL_Node *enq_DLL(DLL_Queue *dll, int ppn) {
    // create a new node with the passed tuple
    DL_Node *node = (DL_Node *)calloc(1, sizeof(DL_Node));
    if (node == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->ppn = ppn;
    node->next = NULL;
    node->prv = NULL;

    if (dll->size == 0) {
        dll->head = node;
    } else {
        dll->tail->next = node;
        node->prv = dll->tail;
    }
    dll->tail = node;
    dll->size++;
    // invrtTable[ppn]->ptr = node;
    return node;
}

int deq_DLL(DLL_Queue *dll) {
    if (dll->size == 0)
        return -1;
    DL_Node *deq_data = dll->head;
    int ret = dll->head->ppn;
    dll->head = dll->head->next;
    if (dll->head != NULL) {
        dll->head->prv = NULL;
    }
    dll->size--;
    if (dll->size == 0)
        dll->tail = NULL;
    // free(deq_data);
    return ret;
}

void del_node(DLL_Queue *dll, DL_Node *node) {
    if (dll->size == 1) {
        dll->head = dll->tail = NULL;
    } else {
        if (dll->head == node) {
            dll->head = node->next;
            dll->head->prv = NULL;
        } else if (dll->tail == node) {
            dll->tail = node->prv;
            dll->tail->next = NULL;
        } else {
            node->prv->next = node->next;
            node->next->prv = node->prv;
        }
    }
    dll->size--;
    // free(node);
}

// test
void print_DL(DLL_Queue *dq) {
    if (dq->size == 0) {
        printf("(empty DLL)\n");
        return;
    }
    DL_Node *cur = dq->head;
    printf("DLL: ");
    while (cur != NULL) {
        printf("%d -> ", cur->ppn);
        cur = cur->next;
    }
}