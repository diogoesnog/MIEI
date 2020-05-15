expAritmeticas: y.tab.o lex.yy.o
	gcc -o expAritmeticas y.tab.o lex.yy.o -ll

y.tab.o: y.tab.c 
	gcc -c y.tab.c 

lex.yy.o: lex.yy.c 
	gcc -c lex.yy.c 

y.tab.c y.tab.h: expAritmeticas.y 
	yacc -d expAritmeticas.y 

lex.yy.c: expAritmeticas.l y.tab.h 
	flex expAritmeticas.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o expAritmeticas 