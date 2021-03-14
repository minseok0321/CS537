/***********************************************************************
* FILENAME : collection.c
*
* DESCRIPTION :
*       This is source file for creating a list of nodes(rules) and 
*       inserting a node to the list of nodes.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/

#include "collection.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function for creating a list of nodes
Group *list_of_rules()
{
  Group *group = malloc(sizeof(Group));
  group->list_size = 1;
  group->list = malloc(group->list_size * sizeof(Node *));
  group->list_idx = 0;
  return group;
}

// function for inserting a node to the list of nodes
void insert_rules(Group *group, Node *rule)
{
  if (group->list_idx == group->list_size)
  {
    group->list_size *= 2;
    group->list = realloc(group->list, group->list_size * sizeof(Node *));
  }
  group->list[group->list_idx++] = rule;
}