/***********************************************************************
* FILENAME : main.c
*
* DESCRIPTION :
*       This is the main source file that executes all the functions
*       needed to make the makefile
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"
#include "parsing_file.h"
#include "parsing_line.h"
#include "exec.h"
#include "cycles.h"

//A main function that calls appropriate functions to parse makefile,
//detect cycle, and build paths according to the provided makefile.
int main(int argc, char **argv)
{
  FILE *f;
  f = fopen("makefile", "r");
  if (f == NULL)
  {
    f = fopen("Makefile", "r");
    if (f == NULL)
    {
      fprintf(stderr, "There is no makefile to be opened.");
    }
  }
  Group *group = parse_file(f);
  if (traverse_dependency(group) == 1)
  {
    printf("%s", "No Cycle Detected.\n");
  }

  char **targets = get_targets(group);
  for (int i = 0; i < group->list_idx; i++)
  {
    traverse(group->list[i], targets, group);
  }

  return 0;
}