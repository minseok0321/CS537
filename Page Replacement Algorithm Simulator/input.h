////////////////////////////////////////////////////////////////////////////////
// Filename: input.h
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date:
////////////////////////////////////////////////////////////////////////////////
#ifndef INPUT_H
#define INPUT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_digit(char *input);
char *read_arg(int argc, char *argv[], int *sizes);
void read_line(FILE *file, long int *pos, int *tuple);

#endif
