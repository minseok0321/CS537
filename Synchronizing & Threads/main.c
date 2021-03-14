/***********************************************************************
* FILENAME : main.c
*
* DESCRIPTION :
*       This is the main source file that executes all the functions
*       for each threads.
*
* AUTHOR : Min Seok Gang
* NetID :   gang3     
* CSLogin : minseok   
* CLASS : CS 537
* TERM : FALL 2020
*
************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include "queue.h"
#include "all_threads.h"

/*
* main function
*   - This function synchronously runs four threads, reader, munch1, munch2, *     munch3, and writer. Creates all these 4 threads, join each of them,      *     prints out the statistics, and frees all the memories created.
*/
int main() {
    const int QUEUE_SIZE = 10;
    Queue *readerTomunch1 = CreateStringQueue(QUEUE_SIZE);
    //need to check???
    Queue *munch1Tomunch2 = CreateStringQueue(QUEUE_SIZE);
    
    Queue *munch2Towriter = CreateStringQueue(QUEUE_SIZE);

    //initialization of four threads
    pthread_t reader;
    pthread_t munch1;
    pthread_t munch2;
    pthread_t writer;
    
    //putting three distinct queues that are shared by assigned counterparts
    void *queues[3];
    queues[0] = readerTomunch1;
    queues[1] = munch1Tomunch2;
    queues[2] = munch2Towriter;
    
    if(pthread_create(&reader, NULL, read_by_line, queues) != 0 || pthread_create(&munch1, NULL, to_asterisk, queues) != 0 || pthread_create(&munch2, NULL, to_upper, queues) != 0 || pthread_create(&writer, NULL, output, queues) != 0){
        fprintf(stderr, "Failed to create a thread");
        exit(1);
    }
    
    if(pthread_join(reader, NULL) != 0 || pthread_join(munch1, NULL) != 0 || pthread_join(munch2, NULL) != 0 || pthread_join(writer, NULL) != 0){
        fprintf(stderr, "Failed to join a thread");
        exit(1);
    }

    //printing out the statistics for each of three queues    
    fprintf(stderr, "Reader-Munch1 Queue Stat\n");
    PrintQueueStats(readerTomunch1);
    fprintf(stderr, "Munch1-Munch2 Queue Stat\n");
    PrintQueueStats(munch1Tomunch2);
    fprintf(stderr, "Munch2-Writer Queue Stat\n");
    PrintQueueStats(munch2Towriter);

    //freeing memory created for buffers and queues
    Queue** qs = (Queue**) queues;
    for(int i = 0 ; i < 3 ; i++){
        free(qs[i]->entry);
	free(qs[i]);
    }
}

