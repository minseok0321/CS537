/***********************************************************************
* FILENAME : all_threads.h
*
* DESCRIPTION :
*       This is the header file for declaring all the functions of each threads *       defined and const int BUFFER_SIZE
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
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

const int BUFFER_SIZE;

void *read_by_line(void *queues);
void *to_asterisk(void *queues);
void *to_upper(void *queues);
void *output(void *queues);