/***********************************************************************
* FILENAME : parsing_file.c
*
* DESCRIPTION :
*       This is the module for parsing the makefile. It tokenizes the
*       dependencies to be stored in a list and same for command lines.
*       Keeps track of number of dependencies and command lines too.
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
#include "parsing_file.h"
#include "ctype.h"

//A function that reads the makefile line by line and call parse_line
//module to return target/dependencies or command line.
Group *parse_file(FILE *f)
{
  char *line = NULL;
  size_t len = 0;
  int line_num = 1;
  int line_size = 0;
  int cmd_idx = 0;
  int add_flag = 0;
  char **result;
  Node *node;
  Group *group = list_of_rules();

  while (getline(&line, &len, f) != -1)
  {
    if (line[0] == '#')
    {
      line_num++;
      continue;
    }
    line_size = strlen(line) + 1;
    int blank_line = 1;
    for (int idx = 0; idx < line_size; idx++)
    {
      if (line[idx] == '\n' && idx == 0)
      {
        break;
      }
      if (!isspace(line[idx]))
      {
        blank_line = 0;
        break;
      }
    }
    if (!blank_line)
    {
      result = parse_line(line, line_num);
    }
    else
    {
      line_num++;
      continue;
    }
    if (strcmp(result[1], "cmd")) //it is target
    {
      if (add_flag)
      {
        insert_rules(group, node);
        node = NULL;
      }
      node = CreateNode(line_size);
      add_flag = 1;
      node->target = result[0];
      node->dependencies = tokenize_dependency(result[1], node);
      cmd_idx = 0;
    }
    else
    {
      if (node == NULL) //Command line without target
      {
        fprintf(stderr, "line: %d, <FORMAT>, command without target", line_num);
        exit(1);
      }
      else
      {
        node->cmd[cmd_idx] = result[0];
        node->num_cmd += 1;
        cmd_idx++;
      }
    }
    line_num++;
  }
  if (node != NULL)
  {
    insert_rules(group, node);
  }
  return group;
}

//A function that tokenizes the dependencies and store each dependency
//file as to form a list of theses
char **tokenize_dependency(char *dependency, Node *node)
{
  int size = 2;
  int idx = 0;
  char **dependencies = malloc(size * sizeof(char *));
  char *pChr = strtok(dependency, " \t\n");
  while (pChr != NULL)
  {
    if (idx == size)
    {
      size = size * 2;
      dependencies = realloc(dependencies, size * sizeof(char *));
    }
    dependencies[idx] = pChr;
    pChr = strtok(NULL, " \t\n");
    idx++;
  }
  node->num_depedencies = idx;
  return dependencies;
}