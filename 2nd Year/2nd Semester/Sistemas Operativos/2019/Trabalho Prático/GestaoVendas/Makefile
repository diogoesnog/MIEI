CC=gcc
CFLAGS=-I

program: cv sv ma ag

cv:	cv.c
	$(CC) -o cv cv.c

sv: sv.c sv.h
	$(CC) -o sv sv.c

ma: ma.c ma.h
	$(CC) -o ma ma.c

ag: ag.c ag.h
	$(CC) -o ag ag.c

clean:
	rm *.txt sv ma cv ag gestorVendas