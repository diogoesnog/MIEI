OPT_OR_DEBUG=-O2
CFLAGS=-Wall -Wextra -pedantic $(OPT_OR_DEBUG)
OBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))


GERADOR: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) 
clean:
	rm GERADOR $(wildcard *.o)


