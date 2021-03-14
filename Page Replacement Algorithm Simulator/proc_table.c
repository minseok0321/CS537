////////////////////////////////////////////////////////////////////////////////
// Filename: proc_table.c
// Authors: David Oh, Minseok Gang
// Email: doh24@wisc.edu, gang3@wisc.edu
// CS login: doh@best-linux.cs.wisc.edu, minseok@best-linux.cs.wisc.edu
// Date: 12/05/2020
////////////////////////////////////////////////////////////////////////////////

#include "proc_table.h"

/*
create and initialize a process struct

input:
    int pid: PID of a process
    void *start: pointer to first instruction

output:
    return the pointer to the new process
*/
Process *createProcess(int pid, long int start) {
    Process *newProc = (Process *)calloc(1, sizeof(Process));
    if (newProc == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newProc->pid = pid;
    newProc->state = 0; //runnable
    newProc->cont_blocks = 1; //number of contiguous blocks of the same process
    newProc->start = newProc->nextStart = newProc->end = start;
    newProc->current = 0;
    newProc->startpoints = create_queue(); //starting position of the each contiguous block for a process
    long int *startPos = (long int *)calloc(1, sizeof(long int));
    if (startPos == NULL) {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    *startPos = start; 
    enqueue(newProc->startpoints, startPos);

    return newProc;
}

/*
update the process table for each trace line

input:
    Queue *procTable: pointer to a process table
    int pid: pid
    void *pos: position of the current trace file
    int prv_pid: previous pid 
*/
void updateProcTable(Queue *procTable, int pid, long int pos, int prv_pid) {
    Process *proc = proc_search(procTable, pid);
    if (proc == NULL) { // new PID reached
        proc = createProcess(pid, pos);
        enqueue(procTable, proc);
    } else { // update existing process info
        proc->end = pos;
        if (prv_pid != pid) {
            long int *startPos = (long int *)calloc(1, sizeof(long int));
            if (startPos == NULL) {
                fprintf(stderr, "error: memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            *startPos = pos;
            //adding the start pos of the contiguous block
            enqueue(proc->startpoints, startPos);
            proc->cont_blocks++;
        }
    }
}

/*
reads the trace file and fill in the process table

input:
    FILE *file: FILE pointer to the trace file
    P_Table *procTable: pointer to a process table
*/
void read_pids(FILE *file, Queue *procTable) {
    int blank = 0;
    int tuple[2];
    int prv_pid = -1;
    long int pos;

    while (1) {
        //end of file reached
        if (feof(file))
            break;
       
        read_line(file, &pos, tuple);
        //checking the line if it was a blank line in the file
        if (tuple[0] != -1) {
            if (blank == 1) {
                fprintf(stderr, "error: blank line\n");
                exit(EXIT_FAILURE);
            }
            updateProcTable(procTable, tuple[0], pos, prv_pid);
            prv_pid = tuple[0];
        } else {
            blank = 1;
        }
    }
}

/*
search for a process with the given pid

input:
    Queue *procTable: pointer to a process table
    int pid: pid

output:
    if the process with the pid exist, return the pointer to that process
    otherwise, return NULL
*/
Process *proc_search(Queue *procTable, int pid) {
    if (procTable->size == 0)
        return NULL;
    Node *curr = procTable->head;
    Process *temp;
    while (curr != NULL) {
        temp = (Process *)(curr->data);
        if (temp->pid == pid)
            return temp;
        curr = curr->next;
    }
    return NULL;
}

/*
Update the current position of the process, the last mapped position of the trace
input:
    Queue *procTable : the table of unique processes
    int pid : the specific pid, process of interest
    long int pos : the last mapped position of the trace of a specific process
                   that is to be updated
output:
    Nothing
*/
void updateCurrent(Queue *procTable, int pid, long int pos) {
    Process *target = proc_search(procTable, pid);
    target->current = pos;
}

/*
block a process in a process table

input:
    Queue *procTable: pointer to a process table
    int pid: pid
    void *pos: position of the current trace file being blocked
*/
void blockProc(Queue *procTable, int pid, Stats *stat) {
    Process *target = proc_search(procTable, pid);
    target->state = 1;
    // target->blocked = pos;
    // int *num_run = procTable->ptr;
    // if (stat->runable_proc != 0)
    //     stat->runable_proc--;
    procTable->ptr = NULL;
    stat->page_faults++;
}

/*
unblock a process in a process table

input:
    Queue *procTable: pointer to a process table
    int pid: pid
*/
void unblockProc(Queue *procTable, int pid) {
    Process *target = proc_search(procTable, pid);
    target->state = 0;
    procTable->ptr = target;
}

/*
Marking the state of the process to be -1 (ran) when the process has
reached its last reference.
input:
    Queue *procTable : a process table
    int pid : the pid of interest
    Stats *stat : statistics that is updated when the process hits its
                  last ref
    int num : number of traces that are being freed due to finishing its
              last ref
output:
    Nothing
*/
void terminate(Queue *procTable, int pid, Stats *stat, int num) {
    Process *target = proc_search(procTable, pid);
    target->state = -1;
    update_pgOcc(stat, -num);
}

/*
Checking if any process is runable from the process table
input:
    Queue *procTable : a process table
output:
    returns 1 when any one of the processes is runable
    returns 0 when all processes are blocked (nothing is runable)
*/
int isRunable(Queue *procTable) {
    Node *curr = procTable->head;
    Process *temp;
    while (curr != NULL) {
        temp = (Process *)(curr->data);
        if (temp->state == 0)
            return 1;
        curr = curr->next;
    }
    return 0;
}

/*
Returns the earliest runable process from the process table
input:
    Queue *procTable: process table
output:
    returns the earliest runable process
*/
Process *earliest_next(Queue *procTable) {
    Node *curr = procTable->head;
    Process *temp;
    Process *ret = NULL;
    long int earl_pos = -1;
    long int tmp_start;
    while (curr != NULL) {
        temp = (Process *)(curr->data);
        if (temp->state == 0) { //when runable
            if (temp->startpoints->size == 0) {
                tmp_start = temp->nextStart;
            } else {
                tmp_start = *((long int *)(temp->startpoints->head->data));
            }
            if (earl_pos == -1) {
                earl_pos = tmp_start;
                ret = temp;
            } else {
                if (earl_pos > tmp_start) {
                    earl_pos = tmp_start; //choosing the position that comes before
                    ret = temp; //choosing that process with earlier position
                }
            }
        }
        curr = curr->next;
    }
    return ret;
}

/*
check whether a process with the given pid is blocked

input:
    Queue *procTable: pointer to a process table
    int pid: pid

output:
    if the process is blocked return 1
    otherwise, return 0

*/
int isBlock(Queue *procTable, int pid) {
    Process *target = proc_search(procTable, pid);
    return target->state;
}

/*
check whether the process with the given pid is read already or not
input:
    Queue *procTable: process table
    int pid : pid
    long int pos : position of the process, line of trace in the trace file
*/
int isRead(Queue *procTable, int pid, long int pos) {
    Process *target = proc_search(procTable, pid);
    if (pos == 0) {
        if (target->start == 0) {
            return 0;
        }
        return 1;
    }
    if (target->current >= target->start) { //
        return target->current >= pos;
    }
    return 0;
}

/*
check whether the given instruction is the last one of a process

input:
    Queue *procTable: pointer to a process table
    int pid: pid
    long int pos: void *pos: position of the current trace file being blocked

output:
    if the process terminates after this instruction, return 1
    otherwise, return 0

*/
int isEnd(Queue *procTable, int pid, long int pos) {
    Process *target = proc_search(procTable, pid);
    return target->end == pos;
}

