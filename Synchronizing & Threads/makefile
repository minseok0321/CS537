#
# Sample makefile updated to include the commands to run the Clang Static Analyzer
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC = gcc
OBJECTS = queue.o stat.o main.o all_threads.o
CFLAGS = -g -Wall -Wextra -pthread
EXE = prodcom
SCAN_BUILD_DIR = scan-build-out

default: main
main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS)

main.o: main.c queue.h stat.h all_threads.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

stat.o: stat.c stat.h
	$(CC) $(CFLAGS) -c stat.c

all_threads.o: all_threads.c all_threads.h
	$(CC) $(CFLAGS) -c all_threads.c


clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
