CC = gcc
FLAGS = -Wall -g

all: server client

server: server.o
	$(CC) $(FLAGS) -o server server.o

client: client.o
	$(CC) $(FLAGS) -o client client.o

server.o: measure.c
	$(CC) $(FLAGS) -c server measure.c

client.o: sender.c
	$(CC) $(FLAGS) -c client sender.c

clean:
	rm -f *.o *.a strings
