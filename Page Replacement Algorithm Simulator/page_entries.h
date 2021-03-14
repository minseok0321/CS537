////////////////////////////////////////////////////////////////////////////////
// Filename: page_entries.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////

#ifndef PAGE_ENTRIES_H
#define PAGE_ENTRIES_H

#include <stdio.h>
#include <stdlib.h>

/*the page entry in the inverted page table that stores each mapped process's 
ref bit, tuple (pid and vpn), and ptr to the page table that stores pid and vpn
*/

typedef struct page_entry {
    int ref_bit;
    int *tuple;
    void *ptr;
} Page_ets;

Page_ets *create_page(int *tuple);

#endif
