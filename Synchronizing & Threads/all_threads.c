/***********************************************************************
* FILENAME : all_threads.c
*
* DESCRIPTION :
*       This is the source file for defining all the functions that arre
*       declared in its header file. Functions of each threads defined.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include "all_threads.h"

/*
* read_by_line function
*   - reading each line of texts from stdin and enqueue each to the queue
*     shared between reader and munch1
*/
void *read_by_line(void *args){
    Queue **queue = (Queue **) args;
    const int BUFFER_SIZE = 50960;
    int index = 0;
    char *line = NULL;
    int buffer_create = 1;
    int skip_line = 0;
    char c = '\0';
    
    //read until end of file
    while((c = getc(stdin)) != EOF){ 
        //creating buffer of fixed size
        if(buffer_create){
            line = calloc(BUFFER_SIZE, sizeof(char));
            if(line == NULL){
                fprintf(stderr, "Failed to allocate memory for buffer.");
                exit(1);
            }    
            buffer_create = 0;
        }
        if(c != '\n'){
            if(index < BUFFER_SIZE){
                line[index] = c;    
                index++;
            }
            //when the length of a line of text exceeds the buffer size
            else{
                fprintf(stderr, "The input exceeds the buffer size.\n");
                //need to skip this line, so set it as 1
                skip_line = 1;
            }
        }
        //characters that are new line
        else{
            //skip_line is off so we enqueue the line of text
            if(!skip_line){
                EnqueueString(queue[0], line);
                line = NULL;
            }
            else{
                //throw away the line of texts whose length is bigger than the buffer size
                free(line);
                line = NULL;
                skip_line = 0;
            }
            index = 0;
            buffer_create = 1;
        }
    }
    //When the last line of texts has no new line, enqueue that line of texts here
    if(line != NULL){
        EnqueueString(queue[0], line);
        line = NULL;
    }
    //indicating the end of the stdin
    EnqueueString(queue[0], NULL);
    pthread_exit(NULL);
}

/*
* to_asterisk function
*   - get each line of texts dequeued from the queue shared with reader 
*     and converts all the whitespaces to asterisk
*/          
void *to_asterisk(void *args){
    Queue **queue = (Queue **) args;
    char *line;
    char *change;
    const char space = ' ';
    while(1){
        line = DequeueString(queue[0]);
        //end when the queue of reader signals end of input
        if(line == NULL){
            break;
        }
        while(1){
            //searching for whitespace in the line of texts and returns the pointer to that position
            change = strchr(line, space);
            if(change == NULL){
                break;    
            }
            //switching whitespaces to asterisk
            else{
                *(change) = '*';    
            }
        }
        EnqueueString(queue[1], line);
    }
    EnqueueString(queue[1], NULL);
    pthread_exit(NULL);
}

/*
* to_upper function
*   - get each line of texts dequeued from the queue shared with munch1 and 
*     converts all lower-case characters to their upper-case
*/          
void *to_upper(void *args){
    Queue **queue = (Queue **) args;
    char *line;
    int index = 0;
    while(1){
        line = DequeueString(queue[1]);
        //end when the queue of munch1 signals end of input
        if(line == NULL){
            break;
        }
        //checking if the characters in a line of texts is an alphabet or not
        while(isalpha(line[index]) || line[index] == '*'){
            if(islower(line[index])){
                line[index] = toupper(line[index]);
            }
            index++;
        }
        EnqueueString(queue[2], line);
        index = 0;
    }
    EnqueueString(queue[2], NULL);
    pthread_exit(NULL);
}

/*
* output function
*   - get each line of texts dequeued from the queue shared with munch2 and 
*     prints each out on the console window
*/ 
void *output(void *args){
    Queue **queue = (Queue **) args;
    char *line;
    while(1){
        line = DequeueString(queue[2]);
        //end when the queue of munch2 signals end of input
        if(line == NULL){
            break;
        }
        printf("%s\n", line);
        free(line);
    }
    pthread_exit(NULL);
}