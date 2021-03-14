CC      = gcc
CFLAGS = -Wall -Wextra
OBJECTS = main.o proc_table.o freelist.o diskQ.o page_entries.o t_map.o input.o queue.o queue_DLL.o stats.o

all: 537pfsim-fifo 537pfsim-lru 537pfsim-clock

537pfsim-fifo: $(OBJECTS) fifo_algorithm.o
	$(CC) $(CFLAGS) -o 537pfsim-fifo $(OBJECTS) fifo_algorithm.o

537pfsim-lru: $(OBJECTS) lru_algorithm.o
	$(CC) $(CFLAGS) -o 537pfsim-lru $(OBJECTS) lru_algorithm.o

537pfsim-clock: $(OBJECTS) clock_algorithm.o
	$(CC) $(CFLAGS) -o 537pfsim-clock $(OBJECTS) clock_algorithm.o

proc_table.o: proc_table.c proc_table.h stats.h queue.h input.h
	$(CC) $(CFLAGS) -c proc_table.c

freelist.o: freelist.c freelist.h page_entries.h t_map.h queue.h
	$(CC) $(CFLAGS) -c freelist.c

diskQ.o: diskQ.c diskQ.h queue.h
	$(CC) $(CFLAGS) -c diskQ.c

t_map.o: t_map.c t_map.h
	$(CC) $(CFLAGS) -c t_map.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

page_entries.o: page_entries.c page_entries.h
	$(CC) $(CFLAGS) -c page_entries.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

queue_DLL.o: queue_DLL.c queue_DLL.h
	$(CC) $(CFLAGS) -c queue_DLL.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

fifo_algorithm.o: fifo_algorithm.c page_algorithm.h
	$(CC) $(CFLAGS) -c fifo_algorithm.c

lru_algorithm.o: lru_algorithm.c page_algorithm.h
	$(CC) $(CFLAGS) -c lru_algorithm.c

clock_algorithm.o: clock_algorithm.c page_algorithm.h
	$(CC) $(CFLAGS) -c clock_algorithm.c

main.o: main.c page_algorithm.h proc_table.h freelist.h diskQ.h page_entries.h t_map.h input.h queue.h queue_DLL.h stats.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f 537pfsim-fifo 537pfsim-lru 537pfsim-clock
	rm -f *.o
