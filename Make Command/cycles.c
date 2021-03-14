/***********************************************************************
* FILENAME : cycles.c
*
* DESCRIPTION :
*       This is the source file for checking a cycle.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include "cycles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A function traversing through all the nodes in the list of nodes and
//check the cycle
int traverse_dependency(Group *rules)
{
  for (int i = 0; i < rules->list_idx; i++)
  {
    detect_cycle(rules->list[i], rules);
  }
  return 1;
}

//A function to detect cycle from a current node in the list of rules
void detect_cycle(Node *current, Group *rules)
{
  if (current->visited == 1)
  {
    fprintf(stderr, "Cycle detected.");
    exit(1);
  }
  if (current->visited == 0)
  {
    current->visited = 1; //updating current node's visited flag
  }
  if (current->num_depedencies != 0)
  {
    for (int i = 0; i < current->num_depedencies; i++)
    {
      for (int j = 0; j < rules->list_idx; j++)
      {
        //when there is a node with target being matched with
        //current node's dependency
        if (!strcmp(current->dependencies[i], rules->list[j]->target))
        {
          detect_cycle(rules->list[j], rules);
          current->visited = 0;
        }
        else
        {
          current->visited = 0;
        }
      }
    }
  }
}