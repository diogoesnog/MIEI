alunos.exe : y.tab.o lex.yy.o
	gcc -o alunos.exe y.tab.o lex.yy.o -ll

y.tab.o : y.tab.c
	gcc -c y.tab.c

lex.yy.o : lex.yy.c
	gcc -c lex.yy.c

y.tab.c y.tab.h : alunos.y
	yacc -d alunos.y 

lex.yy.c : alunos.l y.tab.h
	flex alunos.l

clean:
	rm -rf lex.yy.c lex.yy.o y.tab.c y.tab.o y.tab.h alunos.exe