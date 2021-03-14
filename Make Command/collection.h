/***********************************************************************
* FILENAME : collection.h
*
* DESCRIPTION :
*       This is the header file for collection.c file
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#ifndef GROUP_H
#define GROUP_H
#include "node.h"

// a group struct that has a list of nodes and total number of nodes
typedef struct
{
  Node **list;
  int list_size;
  int list_idx;
} Group;

Group *list_of_rules();
void insert_rules(Group *lists, Node *rule);

#endif