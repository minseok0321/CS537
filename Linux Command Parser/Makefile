CC = gcc
CFLAGS = -Wall -pedantic -g
OBJECTS = proc.o s_parser.o main.o

537ps: $(OBJECTS)
	$(CC) $(CFLAGS) -o 537ps $(OBJECTS)

main.o: main.c proc.h s_parser.h
	$(CC) $(CFLAGS) -c main.c
    
proc.o: proc.c proc.h s_parser.h
	$(CC) $(CFLAGS) -c proc.c
    
s_parser.o: s_parser.c s_parser.h
	$(CC) $(CFLAGS) -c s_parser.c

clean:
	rm -f $(OBJECTS) 537ps
