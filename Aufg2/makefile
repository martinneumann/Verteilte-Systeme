CFLAGS = -Wall
CC = gcc

default: Client Server
	

Client: Client.o
	$(CC) -Wall -o Client Client.c

Server: Server.o
	$(CC) -Wall -o Server Server.c

clean:
	-rm -f Client Server *.o *~    
