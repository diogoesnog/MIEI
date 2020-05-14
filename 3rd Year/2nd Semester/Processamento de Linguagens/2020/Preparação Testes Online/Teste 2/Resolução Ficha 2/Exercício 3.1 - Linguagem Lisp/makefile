mkfromtemplate: linguagemLisp.l
	flex linguagemLisp.l
	cc -o linguagemLisp lex.yy.c

clean:
	rm -rf lex.yy.c linguagemLisp