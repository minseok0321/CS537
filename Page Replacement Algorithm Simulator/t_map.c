////////////////////////////////////////////////////////////////////////////////
// Filename: t_map.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////
#include "t_map.h"

/*
create a node like structure that stores both (PID,VPN)
and corresponding PPN
input:
    int *tuple: PID and VPN
    int ppn: PPN
output:
    if the string is a number representation, return 1
    otherwise, return 0
*/
Entry *create_Entry(int *tuple, int ppn) {
    Entry *e = (Entry *)calloc(1, sizeof(Entry));
    if (e == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    e->tuple = tuple;
    e->ppn = ppn;
    return e;
}

/*
Create a page table with a dummy node included
input:
    Nothing
output:
    A page table (binary tree)
*/
PageTable *create_PT() {
    PageTable *pt = (PageTable *)calloc(1, sizeof(PageTable));
    if (pt == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    pt->root = NULL;
    int *temp = (int *)calloc(2, sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    temp[0] = -1;
    temp[1] = 0;

    Entry *dummy = create_Entry(temp, 0);
    tsearch(dummy, &(pt->root), compare); //inserting dummy node
    pt->size = 0;
    return pt;
}

/*
insert a node structure into the binary tree using tsearch
input:
    PageTable *pt : the binary tree of page table
    int *tuple : pid and vpn
    int ppn : ppn
output:
    void ** : pointer to the node in the page table(binary tree)
*/
void **map_in_tree(PageTable *pt, int *tuple, int ppn) {
    int *tags = (int*)calloc(2, sizeof(int));
    if(tags == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    //making a heap memory for the tuple
    tags[0] = tuple[0];
    tags[1] = tuple[1];

    Entry *entry = create_Entry(tags, ppn);
    void **ret;
    ret = tsearch(entry, &(pt->root), compare);
    if (ret == NULL) {
        fprintf(stderr, "error: tree serach error\n");
        exit(EXIT_FAILURE);
    }
    pt->size++;
    return ret;
}

/*
Freeing the page from the page table
input:
    PageTalbe *pt : page table (binary tree)
    int *tuple : pid and vpn
output:
    Nothing
*/
void free_page(PageTable *pt, int *tuple) {
    Entry entry;
    entry.tuple = tuple;
    tdelete(&entry, &(pt->root), compare);
    pt->size--;
}

/*
Check to see if there is a node in the binary tree
input:
    PageTable *pt : page table
    int *tuple: PID and VPN
output:
    Entry pointer to the node that has been found.
    If not found, return null.
*/
Entry *lookup(PageTable *pt, int *tuple) {
    if (pt->root == NULL) {
        return NULL;
    }
    Entry entry;
    entry.tuple = tuple;
    void **ret;

    ret = tfind(&entry, &(pt->root), compare);
    if (ret == NULL) { // failed to find it
        return NULL;
    }
    return (Entry *)(*ret);
}

/*
Compare function for searching the node in the binary tree
input:
    void *node1: the node to compare
    void *node2: the node to be compared
output:
    return 0 when found the node that we want
    return 1 when the node looking for is the right child
    return -1 when the node looking for is the left tree
*/
int compare(const void *node1, const void *node2) {
    const Entry *e1, *e2;
    e1 = (const Entry *)node1;
    e2 = (const Entry *)node2;

    // just comparing PID
    if (e1->tuple[0] > e2->tuple[0]) {
        return 1;
    } else if (e1->tuple[0] < e2->tuple[0]) {
        return -1;
    } else {
        //comparing VPN
        if (e1->tuple[1] == e2->tuple[1]) {
            return 0;
        } else if (e1->tuple[1] > e2->tuple[1]) {
            return 1;
        } else {
            return -1;
        }
    }
}
