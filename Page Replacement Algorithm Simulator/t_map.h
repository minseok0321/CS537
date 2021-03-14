////////////////////////////////////////////////////////////////////////////////
// Filename: t_map.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////
#ifndef T_MAP_H
#define T_MAP_H

#define _GNU_SOURCE
#include <errno.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
An entry struct in the binary tree that stores the tuple and ppn
*/
typedef struct t_entry {
    int *tuple;
    int ppn;
} Entry;

/*
A page table struct that is a binary tree having entries
It has root entry and the size of the tree
*/
typedef struct page_table {
    void *root;
    int size;
} PageTable;

Entry *create_Entry(int *tuple, int count);
PageTable *create_PT();
void **map_in_tree(PageTable *pt, int *tuple, int ppn);
void free_page(PageTable *pt, int *tuple);
Entry *lookup(PageTable *pt, int *tuple);
int compare(const void *node1, const void *node2);

#endif
