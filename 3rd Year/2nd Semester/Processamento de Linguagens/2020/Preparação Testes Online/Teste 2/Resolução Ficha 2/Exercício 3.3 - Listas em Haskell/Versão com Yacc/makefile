listasHaskell: y.tab.o lex.yy.o
	gcc -o listasHaskell y.tab.o lex.yy.o -ll

y.tab.o: y.tab.c 
	gcc -c y.tab.c 

lex.yy.o: lex.yy.c 
	gcc -c lex.yy.c 

y.tab.c y.tab.h: listasHaskell.y 
	yacc -d listasHaskell.y 

lex.yy.c: listasHaskell.l y.tab.h 
	flex listasHaskell.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o listasHaskell 