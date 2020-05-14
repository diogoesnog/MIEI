mkfromtemplate: listasHaskell.l
	flex listasHaskell.l
	cc -o listasHaskell lex.yy.c

clean:
	rm -rf lex.yy.c listasHaskell