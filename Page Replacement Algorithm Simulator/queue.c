////////////////////////////////////////////////////////////////////////////////
// Filename: queue.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/*
Returns the queue that has head, tail, and pointer reference to the page table,
and the its size
input:
    Nothing
output:
    A queue struct
*/
Queue *create_queue() {
    Queue *q = (Queue *)calloc(1, sizeof(Queue));
    if (q == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    q->head = NULL;
    q->tail = NULL;
    q->ptr = NULL;
    q->size = 0;
    return q;
}

/*
Enqueues the data to the queue by converting it into the node type
intput:
    Queue *q : queue
    void *data : the data such as pid and vpn
output:
    returns the node that has been recently enqueued
*/
Node *enqueue(Queue *q, void *data) {
    // create a new node with the passed tuple
    Node *node = (Node *)calloc(1, sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;

    if (q->size == 0) {
        q->head = node;
    } else {
        q->tail->next = node;
    }
    q->tail = node;
    q->size++;
    return node;
}

/*
Returns the data (pid and vpn) of the head node of the queue
intput:
    Queue *q : queue
output:
    returns the data of the head node from the queue (dequeue it)
*/
void *dequeue(Queue *q) {
    if (q->size == 0) {
        return NULL;
    }
    Node *dqNode = q->head;
    void *ret = dqNode->data;
    q->head = q->head->next;
    q->size--;
    if (q->size == 0) {
        q->tail = NULL;
    }
    return ret;
}

/*
Returns the data of the head node of the queue without dequeuing
intput:
    Queue *q: queue
output:
    returns the data of the head node from the queue (just peeking)
*/
void *peek(Queue *q) {
    if (q->size == 0)
        return NULL;
    return q->head->data;
}
