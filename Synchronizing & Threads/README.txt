CS 537 P_2 by Minseok Gang

Description:

This program implements a simple multi-threaded program using pthread. The 4 threads are reader, munch1, munch2, and writer.
The threads enqueue and dequeue a line of texts to its counterpart and such is controlled by implementing semaphores.
The reader thread reads each line of texts from stdin and enqueue those lines of texts to the queue shared with munch1.
The munch1 thread reads each line of texts from reader by dequeuing from the queue shared with the reader and converts all the white spaces with asterisk. After doing so, it enqueues the modified lines of texts to munch2 with another queue that is shared between munch1 and munch2.
The munch2 thread reads each line of texts from munch1 by dequeuing from the queue shared with the munch1 and converts all the lower-case characters to their upper-case. After doing so, it enqueues the modified lines of texts to writer with another queue that is shared between munch2 and writer.
The writer thread reads each line of texts from munch2 by dequeuing from the queue shared with the munch2 and prints them out to the console to present user final output of the modified lines of texts.

Modules:

The queue.c module creates a queue struct that stores a max 10 lines of texts, allow enqueue and dequeue strings synchronously by using semaphores, and print statistics of the enqueue/dequeue process (each of their counts and time used) with stat.c module.
The stat.c module accesses the enqueue/dequeue counts and times and prints it out on the console for each queue created.
The all_threads.c module has all functions needed for each threads such as reading in lines of texts, converting white-space to asterisk, switching lower-case to upper-case, and printing out the modified version of texts on the console.
The main.c module is the main module that runs the program. It initializes the threads and queues, prints the statistics for each queue, and free all of the allocated memory on heap used by this program.