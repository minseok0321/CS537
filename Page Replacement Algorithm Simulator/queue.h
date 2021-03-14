////////////////////////////////////////////////////////////////////////////////
// Filename: queue.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////
#ifndef QUEUE_H
#define QUEUE_H

/*
A node struct that stores data (pid and vpn) and the next node
*/
typedef struct node {
    void *data;
    struct node *next;
} Node;

/*
A queue struct that stores nodes with head and tail pointer, pointer to the page
table, and the size of the queue
*/
typedef struct queue {
    Node *head;
    Node *tail;
    void *ptr;
    int size;
} Queue;

Queue *create_queue();
Node *enqueue(Queue *q, void *data);
void *dequeue(Queue *q);
void *peek(Queue *q);

#endif
