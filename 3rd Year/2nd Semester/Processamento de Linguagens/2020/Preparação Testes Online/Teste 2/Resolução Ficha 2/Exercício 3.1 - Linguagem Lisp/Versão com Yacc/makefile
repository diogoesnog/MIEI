linguagemLisp: y.tab.o lex.yy.o
	gcc -o linguagemLisp y.tab.o lex.yy.o -ll

y.tab.o: y.tab.c 
	gcc -c y.tab.c 

lex.yy.o: lex.yy.c 
	gcc -c lex.yy.c 

y.tab.c y.tab.h: linguagemLisp.y 
	yacc -d linguagemLisp.y 

lex.yy.c: linguagemLisp.l y.tab.h 
	flex linguagemLisp.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o linguagemLisp 