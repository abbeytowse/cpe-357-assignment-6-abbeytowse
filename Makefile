CC = gcc
CFLAGS = -Wall -g -std=c99 -pedantic 
MAIN= main
MAIN_OBJS = main.o array_list.o operations.o util.o
PROGS = $(MAIN) 

all : $(MAIN)

$(MAIN) : $(MAIN_OBJS) main.h
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN_OBJS)

main.o : main.c main.h
	$(CC) $(CFLAGS) -c main.c

array_list.o : array_list.c array_list.h	
	$(CC) $(CFLAGS) -c array_list.c

operations.o : operations.c operations.h
	$(CC) $(CFLAGS) -c operations.c

util.o : util.c util.h 
	$(CC) $(CFLAG) -c util.c

clean :
	rm *.o $(PROGS) core
