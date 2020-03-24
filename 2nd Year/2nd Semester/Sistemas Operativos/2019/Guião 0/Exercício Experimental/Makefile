CFLAGS = -g -Wall
LDFLAGS = -g

program: mod.o program.o
mod.o: mod.c mod.h
program.o: program.c mod.h
clean:
	rm -f program *.o