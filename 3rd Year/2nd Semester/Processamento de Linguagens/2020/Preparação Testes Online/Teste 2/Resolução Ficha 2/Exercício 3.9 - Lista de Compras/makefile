listaCompras: y.tab.o lex.yy.o
	gcc -o listaCompras y.tab.o lex.yy.o -ll

y.tab.o: y.tab.c 
	gcc -c y.tab.c 

lex.yy.o: lex.yy.c 
	gcc -c lex.yy.c 

y.tab.c y.tab.h: listaCompras.y 
	yacc -d listaCompras.y 

lex.yy.c: listaCompras.l y.tab.h 
	flex listaCompras.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o listaCompras 