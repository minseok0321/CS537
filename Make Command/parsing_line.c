/***********************************************************************
* FILENAME : parsing_line.c
*
* DESCRIPTION :
*       This is the module for getting in a line from a makefile and 
*       return either a target and dependencies or command line
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
#include "parsing_line.h"

//A function that determines whether the line is target and dependencies
//or command line. Returns a target/dependencies or a command line.
char **parse_line(char *line, int line_num)
{
  const int BUFFER_SIZE = 4096;
  int size = 2;
  int line_size = strlen(line) + 1;
  int dpd_flag = 0;
  int dpd_idx = 0;
  char *target = NULL;
  char *dpds = NULL;
  char *cmds;
  char **result = malloc(size * sizeof(char *));

  if (line_size > BUFFER_SIZE)
  {
    fprintf(stderr, "%d: <OVERFLOW>: %s\n", line_num, line);
    exit(1);
  }
  else
  {

    if (line[0] == '\t')
    {
      cmds = malloc(line_size * sizeof(char));
      for (int k = 0; k < line_size; k++)
      {
        cmds[k] = line[k];
      }
      result[0] = cmds;
      result[1] = "cmd";
      cmds = NULL;
    }
    if (line[0] != '\t')
    {
      target = malloc(line_size * sizeof(char));
      dpds = malloc(line_size * sizeof(char));
      for (int i = 0; i < line_size; i++)
      {
        if (line[i] == ':')
        {
          dpd_flag = 1;
        }
        if (!dpd_flag)
        {
          target[i] = line[i];
        }
        if (dpd_flag)
        {
          for (int j = i + 1; j < line_size; j++)
          {
            dpds[dpd_idx] = line[j];
            dpd_idx++;
          }
          break;
        }
      }
      if (dpd_flag == 0)
      {
        fprintf(stderr, "%d: <Missing colon>: %s\n", line_num, line);
        exit(1);
      }
      result[0] = target;
      result[1] = dpds;
    }
  }
  return result;
}