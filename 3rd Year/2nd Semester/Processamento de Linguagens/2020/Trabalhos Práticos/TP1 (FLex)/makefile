mkfromtemplate: mkfromtemplate.l
	flex mkfromtemplate.l
	cc -o mkfromtemplate lex.yy.c directories.c

clean:
	rm -rf lex.yy.c mkfromtemplate */