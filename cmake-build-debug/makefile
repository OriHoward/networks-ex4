CC = gcc
FLAGS = -Wall -g

all: server client

server: measure.o
	$(CC) $(FLAGS) -o server measure.o

client: sender.o
	$(CC) $(FLAGS) -o client sender.o

measure.o: measure.c
	$(CC) $(FLAGS) -c measure.c

sender.o: sender.c
	$(CC) $(FLAGS) -c sender.c

clean:
	rm -f *.o *.a strings
