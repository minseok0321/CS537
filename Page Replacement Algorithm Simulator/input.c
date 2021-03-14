////////////////////////////////////////////////////////////////////////////////
// Filename: input.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////

#include "input.h"

/*
check the input whether it's a digit number

input:
    char *input: string to check
output:
    if the string is a number representation, return 1
    otherwise, return 0
*/
int is_digit(char *input) {
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        if (isdigit(input[i]) == 0)
            return 0;
    }
    return 1;
}

/*
reads the command line and returns the sizes of page and memory

input:
    int argc: number of arguments
    char *argv[]: array of arguments

output:
    array of integers with the sizes of page and memory
*/
char *read_arg(int argc, char *argv[], int *sizes) {
    int opt;
    char *temp = NULL;
    
    // parse the argument and read each option
    while (optind < argc) {
        if ((opt = getopt(argc, argv, "p:m:")) == -1) {
            if (temp != NULL) {
                fprintf(stderr,
                        "Usage: %s [-p pagesize(bytes)] [-m "
                        "memorysize(MB)] tracefile\n",
                        argv[0]);
                exit(EXIT_FAILURE);
            }
            temp = argv[optind];
            optind++;
            continue;
        }
        switch (opt) {
        case 'p':
            if (optarg == NULL || is_digit(optarg) == 0) {
                fprintf(stderr, "error: enter digit page size\n");
                exit(EXIT_FAILURE);
            }
            sizes[0] = atoi(optarg);
            break;

        case 'm':
            if (optarg == NULL || is_digit(optarg) == 0) {
                fprintf(stderr, "error: enter digit memory size\n");
                exit(EXIT_FAILURE);
            }
            sizes[1] = atoi(optarg);
            break;
        case '?':
            fprintf(stderr,
                    "Usage: %s [-p pagesize(bytes)] [-m "
                    "memorysize(MB)] tracefile\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (temp == NULL) {
        fprintf(stderr, "error: need trace file name\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

/*
reads the line from the file indicated by specific position and
puts the necessary info (pid, vpn) into the tuple pointer.

input:
    FILE *file : trace file
    long int *pos : the position of the trace that needs to be read 
                    (specific line in the file)
    int *tuple : the place where to store the necessary info such as
                 PID and VPN

output:
    Nothing
*/
void read_line(FILE *file, long int *pos, int *tuple) {
    const int MAX_INT_LEN = 10;

    int t_index = 0;
    int s_index = 0;
    int s_flag = 0;
    char c;
    char pid[MAX_INT_LEN];
    char vpn[MAX_INT_LEN];
    memset(pid, 0, MAX_INT_LEN);
    memset(vpn, 0, MAX_INT_LEN);

    *pos = ftell(file);
    while ((c = getc(file)) != '\n') { // c gets char until the end of line
        // EOF reached
        if (c == EOF) {
            tuple[0] = -1;
            return;
        }
        //checking if c is a digit or not / checking white space too
        if (isdigit(c) == 0 && c != ' ') {
            fprintf(stderr, "error: size should be a digit number\n");
            exit(EXIT_FAILURE);
        }
        if (c == '\0') { // null bytes within the line
            fprintf(stderr, "error: line containing null byte\n");
            exit(EXIT_FAILURE);
        }

        if (t_index == 0) { // reading PID
            if (s_flag == 0) {
                if (c != ' ') {
                    strncat(pid, &c, 1);
                    s_flag = 1;
                } else {
                    s_index++;
                }
            } else { // start index locked
                if (c == ' ') {
                    t_index++;
                    s_flag = 0;
                } else {
                    strncat(pid, &c, 1);
                }
            }
        } else if (t_index == 1) { // reading VPN
            if (s_flag == 0) {
                if (c != ' ') {
                    strncat(vpn, &c, 1);
                    s_flag = 1;
                }
            } else { // start index locked
                if (c == ' ') {
                    t_index++;
                    s_flag = 0;

                } else {
                    strncat(vpn, &c, 1);
                }
            }
        } else {
            if (c != ' ') {
                fprintf(stderr, "error: more than two integers in line\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    if (t_index == 0) {
        if (s_index != 0) {
            // blank line in the middle trace file
            fprintf(stderr, "error: blank line\n");
            exit(EXIT_FAILURE);
        }
        tuple[0] = -1;
        return ;
    }
    if (t_index != 1) {
        fprintf(stderr, "error: need two integers for PID and VPN\n");
        exit(EXIT_FAILURE);
    }
    //stores the necessary info into the tuple pointer passed in as a param
    tuple[0] = atoi(pid);
    tuple[1] = atoi(vpn);
}
