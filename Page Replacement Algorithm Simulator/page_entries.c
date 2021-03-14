////////////////////////////////////////////////////////////////////////////////
// Filename: page_entries.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////

#include "page_entries.h"

/*
returns the page frame with necessary information updated
input:
    int *tuple : tuple of pid and vpn
output:
    returns the page with ref bit, tuple of pid and vpn, and ptr to the page table
    that stores the tuple of pid and vpn
*/
Page_ets *create_page(int *tuple)
{
  Page_ets *page = (Page_ets *)calloc(1, sizeof(Page_ets));
  if(page == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
  page->ref_bit = 1;
  page->tuple = tuple;
  page->ptr = NULL;

  return page;
}
