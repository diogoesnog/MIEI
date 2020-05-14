linguagemParent: y.tab.o lex.yy.o
	gcc -o linguagemParent y.tab.o lex.yy.o -ll

y.tab.o: y.tab.c 
	gcc -c y.tab.c 

lex.yy.o: lex.yy.c 
	gcc -c lex.yy.c 

y.tab.c y.tab.h: linguagemParent.y 
	yacc -d linguagemParent.y 

lex.yy.c: linguagemParent.l y.tab.h 
	flex linguagemParent.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o linguagemParent 