calculator.exe : y.tab.o lex.yy.o read.o
	gcc -o calculator.exe y.tab.o lex.yy.o read.o -ll

y.tab.o : y.tab.c
	gcc -c y.tab.c

lex.yy.o : lex.yy.c
	gcc -c lex.yy.c

y.tab.c y.tab.h : calculator.y
	yacc -d calculator.y 

lex.yy.c : calculator.l y.tab.h
	flex calculator.l

read.o : read.c read.h
	gcc -c read.c

clean:
	rm -rf lex.yy.c lex.yy.o y.tab.c y.tab.o y.tab.h read.o calculator.exe