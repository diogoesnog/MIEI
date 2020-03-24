%{

	int r = 0;

%}

%%
\<[^>]*\> {ECHO;}
("+351-")?[0-9]{9} {ECHO; r++; printf("\n");}
.|\n
%%

int yywrap(){
	return 1;
}

int main(){
	yylex();
	printf("Total de números: %d \n", r);
	return 0;
}