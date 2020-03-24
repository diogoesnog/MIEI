CC = gcc
CFLAGS = -Wall

program: person
	$(CC) $(CFLAGS) program.c -o program person.o

person:
	$(CC) $(CFLAGS) -c person.c

clean:
	rm program person.o