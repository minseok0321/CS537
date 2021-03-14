/***********************************************************************
* FILENAME : exec.h
*
* DESCRIPTION :
*       This is the header file for the exec.c module.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include "collection.h"
#include "node.h"

char **get_targets(Group *group);
void traverse(Node *node, char **targets, Group *group);
char **tokenize(char *command);