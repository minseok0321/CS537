#ifndef QUEUE_DLL_H
#define QUEUE_DLL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct d_node {
    int ppn;
    struct d_node *next;
    struct d_node *prv;
} DL_Node;

typedef struct doubleLL {
    DL_Node *head;
    DL_Node *tail;
    void *node_ptr;
    int size;
} DLL_Queue;

DLL_Queue *create_DLL();
DL_Node *enq_DLL(DLL_Queue *dll, int ppn);
int deq_DLL(DLL_Queue *dll);
void del_node(DLL_Queue *dll, DL_Node *node);
void print_DL(DLL_Queue *dq);

#endif