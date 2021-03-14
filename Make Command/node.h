/***********************************************************************
* FILENAME : node.h
*
* DESCRIPTION :
*       This is the header file for node.c module.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#ifndef NODE_H
#define NODE_H

typedef struct
{
  char *target;
  char **dependencies;
  char **cmd;
  int num_depedencies;
  int num_cmd;
  int visited;
} Node;

Node *CreateNode(int size);

#endif