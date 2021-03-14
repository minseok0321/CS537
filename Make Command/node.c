/***********************************************************************
* FILENAME : node.c
*
* DESCRIPTION :
*       This is the module for creating a node that has a target name,
*       a list of dependencies, a list of commands, a number of dependencies
*       a number of commands, and a flag for tracking whether a node has 
*       been visited or not.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include "node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//A function that initializes the node and its members that exist in the
//node struct.
Node *CreateNode(int size)
{
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for specification");
    exit(1);
  }
  node->target = (char *)malloc(size * sizeof(char));
  if (node->target == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for target");
    exit(1);
  }
  node->cmd = (char **)malloc(size * sizeof(char *));
  if (node->cmd == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for command line");
    exit(1);
  }
  node->dependencies = (char **)malloc(size * sizeof(char *));
  if (node->dependencies == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for array for dependencies");
    exit(1);
  }
  node->num_depedencies = 0;
  node->num_cmd = 0;
  node->visited = 0;

  return node;
}
