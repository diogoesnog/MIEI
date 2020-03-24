jornal: jornal.fl estrutura.c tags.c
	flex jornal.fl
	cc -o jornal tags.c estrutura.c lex.yy.c

clean:
	rm -f lex.yy.c jornal *.html estrutura.txt