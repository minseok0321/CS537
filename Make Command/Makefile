537make: main.o parsing_file.o parsing_line.o node.o collection.o cycles.o exec.o
	gcc -o 537make parsing_line.o parsing_file.o main.o node.o collection.o cycles.o exec.o

main.o: main.c parsing_file.h node.h collection.h parsing_line.h collection.h cycles.h exec.h
	gcc -c -Wall -Wextra main.c

parsing_line.o: parsing_line.c parsing_line.h node.h
	gcc -c -Wall -Wextra parsing_line.c

parsing_file.o: parsing_file.c parsing_line.h
	gcc -c -Wall -Wextra parsing_file.c

node.o: node.c node.h
	gcc -c -Wall -Wextra node.c
     
collection.o: collection.c node.h collection.h
	gcc -c -Wall -Wextra collection.c

cycles.o: cycles.c cycles.h
	gcc -c -Wall -Wextra cycles.c

exec.o: exec.c exec.h
	gcc -c -Wall -Wextra exec.c

clean:
	-rm *.o 537make