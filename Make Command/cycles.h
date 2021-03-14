/***********************************************************************
* FILENAME : cycles.h
*
* DESCRIPTION :
*       This is the header file for the cycles.c module
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#ifndef CYCLE_H
#define CYCLE_H

#include "collection.h"
#include "node.h"

int traverse_dependency(Group *rules);
void detect_cycle(Node *current, Group *rules);

#endif