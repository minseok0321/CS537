/***********************************************************************
* FILENAME : exec.c
*
* DESCRIPTION :
*       This is the source file for executing the commands, forking 
*       process, and tokenize commands to fit into the execvp function.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "exec.h"

//A function to get a list of all targets from the makefile
char **get_targets(Group *group)
{
  int idx;
  char **targets = malloc(group->list_idx * sizeof(char *));
  for (idx = 0; idx < group->list_idx; idx++)
  {
    targets[idx] = group->list[idx]->target;
  }
  return targets;
}

//A function that traverse through the list of nodes and executing
//commands in post-traversal order
void traverse(Node *node, char **targets, Group *group)
{
  int num = node->num_depedencies;
  int i;
  int j;
  for (i = 0; i < num; i++)
  {
    for (j = 0; j < group->list_idx; j++)
    {
      if (!strcmp(node->dependencies[i], targets[j]))
      {
        traverse(group->list[j], targets, group);
      }
    }
  }

  struct stat attr1;
  struct stat attr2;
  stat(node->target, &attr1);
  //storing mod. time for the target
  time_t target_time = attr1.st_mtime;
  time_t dpd_time;
  pid_t child_PID;
  int status;

  //checking if any of the dependencies has been modified later
  for (int k = 0; k < node->num_depedencies; k++)
  {
    stat(node->dependencies[k], &attr2);
    dpd_time = attr2.st_mtime;
    //has been modified later
    if (difftime(dpd_time, target_time) > 0)
    {
      int c;
      for (c = 0; c < node->num_cmd; c++)
      {
        char **token = tokenize(node->cmd[c]);
        child_PID = fork();
        if (child_PID == 0)
        {
          execvp(token[0], token);
        }
        else if (child_PID > 0)
        {
          if (wait(&status) < 0)
          {
            fprintf(stderr, "Process on wait");
            exit(1);
          }
        }
        else
        {
          fprintf(stderr, "Forking has failed.");
          exit(1);
        }
      }
    }
  }
}

//A function to tokenize the command separated by whitespace
//to match the format in execvp function
char **tokenize(char *command)
{
  int size = 2;
  int idx = 0;
  char **argv = malloc(size * sizeof(char *));
  char *pChr = strtok(command, " ");
  while (pChr != NULL)
  {
    if (idx == size)
    {
      size = size * 2;
      argv = realloc(argv, size * sizeof(char *));
    }
    argv[size] = pChr;
    pChr = strtok(NULL, " ");
    size++;
  }
  argv[size] = NULL;
  return argv;
}