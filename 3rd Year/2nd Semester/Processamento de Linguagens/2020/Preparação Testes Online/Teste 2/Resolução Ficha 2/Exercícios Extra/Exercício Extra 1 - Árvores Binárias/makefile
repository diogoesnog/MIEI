arvoreBin: y.tab.o lex.yy.o
	gcc -o arvoreBin y.tab.o lex.yy.o -ll

y.tab.o: y.tab.c 
	gcc -c y.tab.c 

lex.yy.o: lex.yy.c 
	gcc -c lex.yy.c 

y.tab.c y.tab.h: arvoreBin.y 
	yacc -d arvoreBin.y 

lex.yy.c: arvoreBin.l y.tab.h 
	flex arvoreBin.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o arvoreBin 