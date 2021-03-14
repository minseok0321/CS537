/***********************************************************************
* FILENAME : parsing_file.h
*
* DESCRIPTION :
*       This is the header file for parsing_file.c module
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
#include "node.h"
#include "collection.h"
#include "parsing_line.h"
#ifndef PARSINGF_H
#define PARSINGF_H

Group *parse_file(FILE *fp);
char **tokenize_dependency(char *dependency, Node *node);

#endif