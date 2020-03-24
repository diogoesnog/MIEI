#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 1024

/*protótipos*/
int bitsUm (unsigned int);
int trailingZ (unsigned int);
int qDig (unsigned int);
int strlen2 (char *);
char *strcat2 (char [], char []);
char *strcpy2 (char *, char []);
int strcmp2 (char [], char []);
char *strstr2 (char [], char []);
void strrev2 (char []);
void strnoV2 (char []);
void truncW (char [], int);
char charMaisfreq (char []);
int iguaisConsecutivos (char []);
int difConsecutivos (char []);
int maiorPrefixo (char [], char []);
int maiorSufixo (char [], char []);
int sufPref (char [], char []);
int contaPal (char []);
int contaVogais (char []);
int contida(char [], char []);
int palindorome (char []); 
int remRep (char []);
int limpaEspacos (char []);
void insere (int [], int, int);
void merge (int [], int [], int [], int, int);
int crescente (int [], int, int);
int retiraNeg (int [], int);
int menosFreq (int [], int);
int maisFreq (int [], int);
int maxCresc (int [], int);
int elimRep (int [], int);
int elimRepOrd (int[], int);
int comunsOrd (int [], int, int[], int);
int comuns (int[], int, int[], int);
int minInd (int [], int);
void somasAc (int[], int[], int);
void addTo (int N, int M, int a [N][M], int b[N][M]);
void sumDiag (int N, int m [N][N]);
int unionSet (int N, int v1[N], int v2[N], int r[N]);
int intersectSet (int N, int v1[N], int v2[N], int r[N]);
int intersectMSet (int N, int v1[N], int v2[N], int r[N]);
int unionMSet (int N, int v1[N], int v2[N], int r[N]);
int cardinalMSet (int N, int v[N]);

int questao1 () {
	int x=1, soma=0;
	printf("Introduza um número (0 corresponde ao fim): \n");
	while (x!=0) {
		scanf("%d",&x);
		soma+=x;
    }
    printf("A soma é: %d\n", soma);
    return 2;
}

int questao2 () {
	int x=1,m=0;
	printf("Insira uma sequência de numeros positivos (0 para terminar):\n");
	while (x) {
		scanf ("%d",&x);
		if (x>m) m=x;
	}
	printf("O maior elemento é: %d\n",m);
	return 2;
}

int questao3 () {
	int x=1, soma=0, total=-1;
	printf("Digite uma sequência terminada em 0:\n");
	while (x) {
		scanf("%d",&x);
		soma+=x;
		total++;
	}
	printf("A média da sequência é: %d\n", soma/total);
	return 2;
}

int questao4 () {
	int x=1, m=0, s=0;
	printf("Digite uma sequência terminada em 0: \n");
	while (x) {
		scanf("%d",&x);
		if (x>m) { s=m; m=x; }
		if (x<m && x>s) s=x;
	}
	printf("O segundo maior elemento é %d.\n", s);
	return 2;
}

int questao5 () {
	int n;
	printf ("Digite um número inteiro positivo:\n");
	scanf("%d",&n);
	printf("O número tem %d dígitos 1 na sua representação binária\n", bitsUm (n));
	return 2;
}

int bitsUm (unsigned int n) { //10 em 10
	int count = 0;
	while (n) {
		if (n%2 == 1) count ++;
		n=n/2;
	}
	return count;
}

int questao6 () {
	int n;
	printf("Escreva um número inteiro positivo:\n");
	scanf("%d",&n);
	printf("O número %d tem %d dígitos 0 no fim da sua representação binária.\n", n, trailingZ(n));
	return 2;
}

int trailingZ (unsigned int n) { //10 em 10
	int count = 0;
	while (n && n%2==0) {
		count++;
		n=n/2;
	}
	return count;
}

int questao7 () {
	int n;
	printf("Digite um número em base décimal:\n");
	scanf("%d",&n);
	printf("O número %d tem %d dígitos.\n", n, qDig(n));
	return 2;
}

int qDig (unsigned int n) { //10 em 10
	int count = 1;
	while (n>=10) {
		count ++;
		n=n/10;
	}
	return count;
}

int questao8 () {
	char str [MAXSIZE];
	printf("Digite uma string.\n");
	scanf ("%[^\n]", str);
	printf("A string %s tem comprimento %d.\n", str, strlen2 (str));
	return 2;
}

int strlen2 (char str[]) { //10 em 10
	int i;
	for(i=0;str[i]!='\0'; i++);
	return i;
}

int questao9 () {
	char s1[MAXSIZE];
	char s2[MAXSIZE];
	char *e;
	printf("Digite uma string:\n");
	scanf ("%s", s1);
	printf("Digite uma segunda string:\n");
	scanf ("%s", s2);
	if ((strlen (s1) + strlen (s2)) >=MAXSIZE) { printf("O tamanho de s1 é insuficiente\n"); return 1; }
	else {
		e = strcat2(s1,s2);
		printf("O endereço é: %s\n", e); /*porque o João diz que o endereço é a string (mas eu não percebo porquê)*/
		printf("A string resultante é: %s\n", s1);
		return 1;
	}
}

char *strcat2 (char s1[], char s2[]) { //10 em 10
	int i, j;
	for (i=strlen (s1), j=0; s2[j]!='\0'; i++,j++) {
		s1[i] = s2[j];
	}
	s1[i]='\0' ;
	return s1;
}

int questao10 () {
	char *dest=(char *)malloc(100);
	char source[MAXSIZE];
	printf("Digite a String fonte:\n");
	scanf("%s", source);
	printf("O valor do destino é %s\n", strcpy2(dest, source));
	return 1;
}

char *strcpy2 (char *dest, char source[]) { //10 em 10
	int i;
	for(i=0;source[i]!='\0';i++) {
		dest[i] = source[i];
	}
	dest[i]='\0';
	return dest;
}

int questao11 () {
	char s1[MAXSIZE];
	char s2[MAXSIZE];
	printf("Insira a primeira string:\n");
	scanf("%s", s1);
	printf("Insira a segunda string:\n");
	scanf("%s", s2);
	printf("O resultado é: %d\n", strcmp2(s1, s2));
	if(strcmp2(s1, s2)<0) printf("A primeira string é menor.\n");
	if(strcmp2(s1, s2)==0) printf("As strings são iguais.\n");
	if(strcmp2(s1, s2)>0) printf("A primeira string é maior.\n");
	return 1;
}

int strcmp2 (char s1[], char s2[]) { //10 em 10
	int i=0;
	while (s1[i]==s2[i] && s1[i]!='\0')
		i++;
	return (s1[i] - s2[i]);
}

int questao12 () {
	char s1[MAXSIZE];
	char s2[MAXSIZE];
	char *e;
	printf("Escreva uma string:\n");
	scanf("%[^\n]", s1);
	getchar(); /*"apanha" o \n que o scanf está a deixar para trás*/
	printf("Escreva uma segunda string:\n");
	scanf("%[^\n]", s2);
	while(s2[0]=='\n') scanf("%[^\n]", s2); /*não funciona no terminal, está a ler o \n como segunda string*/
	e=strstr2(s1, s2);
	if (e==NULL) printf("A string %s não ocorre em %s.\n", s2, s1);
	else printf("A string %s ocorre em %s. Solução: %s. \n", s2, s1, e);
	return 1;
}

char *strstr2 (char s1[], char s2[]) { //10 em 10
	int i, j;
	if(s1[0]=='\0' && s2[0]=='\0') return s1;
	for (i=0; s1[i]!='\0'; i++) {
		int s=0; j=i;
		while (s1[j]==s2[s] && s1[j]!='\0') {
			s++; j++;
		}
		if (s2[s]=='\0') {
		    return &s1[i]; break;}
	}
	return NULL;
}

int questao13 () {
	char s[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s);
	strrev2(s);
	printf("A string inversa é %s.\n", s);
	return 1;
}

void strrev2 (char s[]) { //10 em 10
	int i, len; char c;
	for (len =0; s[len]!='\0';len++);
	for (i=0; i<len/2; i++) {
		c=s[i];
		s[i]=s[len-1-i];
		s[len-1-i]=c;
	}
}

int questao14 () {
	char s[MAXSIZE];
	printf("Escreva uma string.\n");
	scanf("%s", s);
	strnoV2(s);
	printf("A string sem vogais é: %s\n", s);
	return 1;
}

void strnoV2 (char s[]) { //10 em 10
	int i, e=0;
	for (i=0; s[i]!='\0'; i++) {
		if (s[i]!='A' && s[i]!='a' && s[i]!='E' && s[i]!='e' && s[i]!='I' && s[i]!='i' && s[i]!='O' && s[i]!='o' && s[i]!='U' && s[i]!='u') {
			s[e]=s[i]; e++;
		}
	}
	s[e]='\0';
}

int questao15 () {
	char t[MAXSIZE];
	int n;
	printf("Escreva uma string: \n");
	scanf("%[^\n]", t);
	printf("Escreva um número para truncar:\n");
	scanf("%d", &n);
	truncW(t, n);
	printf("A string truncada é %s.\n", t);
	return 1;
}

void truncW (char t[], int n) { //10 em 10
	int i=0, e=0, c=n;
	while (t[i]!='\0') {
		if(isspace(t[i])) {
			t[e] = t[i];
			e++; i++; c=n;
			}
		else {
			if (c!=0) {
				t[e] = t[i];
				e++; i++; c--;
			}
			else i++;
		}
	}
	t[e]='\0';
}

int questao16 () {
	char s[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s);
	printf("O char mais frequente é: %c\n", charMaisfreq(s));
	return 1;
}
char charMaisfreq (char s[]) { //10 testes de 10
	int i, j, c, m=0; char f='0';
	for (i=0; s[i]!='\0'; i++) {
		c=0;
		for (j=0; s[j]!='\0'; j++) {
			if (s[i]==s[j]) c++;
		}
		if (c>m) { m=c; f = s[i];}
	}
	return f;
}

int questao17 () {
	char s[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s);
	printf("O comprimento da maior sub-string com caracteres iguais é: %d\n", iguaisConsecutivos(s));
	return 1;
}

int iguaisConsecutivos (char s[]) { //10 em 10
	int i, c=1, m=0;
	for (i=0; s[i+1]!='\0'; i++) {
		if (s[i]!=s[i+1]) c=1;
		if (s[i]== s[i+1]) c++;
		if (c>m) m=c;
	}
	return m;
}

int questao18 () {
	char s[MAXSIZE];
	printf("Escreva uma string sem espaços: \n");
	scanf("%s", s);
	printf("O comprimento da maior sub-string com caracteres diferentes é: %d\n", difConsecutivos(s));
	return 1;
}

int pertence1 (char s[], char x, int j) {
    int i;
    for(i=0;i<j&&s[i]!=x;i++);
    if(i<j && s[i]==x) return 1;
    return 0;
}

int difConsecutivos (char s[]) { //10 em 10
    int i, j=0, k=1, m=0;
    for(i=0;s[i]!='\0';i++);
    char aux[i]; i=0;
    if(s[0]=='\0') return 0;
    else if(s[1]=='\0') return 1;
    else while(s[i]!='\0') {
	    	if(i==0) {
		      aux[0]=s[i];j++; i++; continue;
	    	}
	    	else if ((s[i]!=s[i-1] || s[i]!=s[i+1])) {
	    	    	if(pertence1(aux, s[i], j)){
				    	if (j>m) {
					    	m=j; 
				    	}
				    	i=k;j=0; k++;
		        	}
			        else {
			    	    aux[j]=s[i];
				        j++; i++;
		    	    }
	    	    }
	        	else {
	    	     if (j>m) m=j; 
	            	j=0; i=k; k++;
	        	}
	    	}
	return m;
}

int questao19 () {
	char s1[MAXSIZE];
	char s2[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s1);
	printf("Escreva uma segunda string:\n");
	scanf("%s", s2);
	printf("O maior prefixo entre as duas strings tem comprimento %d.\n", maiorPrefixo(s1,s2));
	return 1;
}

int maiorPrefixo (char s1[], char s2[]) { //10 em 10
 int i;
 for (i=0;s1[i]!='\0' && s2[i]!='\0' && s1[i]==s2[i];i++);
 return i;
}

int questao20 () {
	char s1[MAXSIZE];
	char s2[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s1);
	printf("Escreva a segunda string:\n");
	scanf("%s", s2);
	printf("O maior sufixo comum entre as strings tem comprimento %d.\n", maiorSufixo(s1, s2));
	return 1;
}

int maiorSufixo (char s1[], char s2[]) { //10 em 10
	int i, j;
	for(i=strlen(s1)-1, j=strlen(s2)-1; i>=0 && j>=0 && s1[i]==s2[j]; i--,j--);
	return (strlen(s1)-i-1);
}

int questao21 () {
	char s1[MAXSIZE];
	char s2[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s1);
	printf("Escreva outra string:\n");
	scanf("%s", s2);
	printf("O tamanho do maior sufixo da primeira string que é um prefixo da segunda é: %d\n", sufPref(s1, s2));
	return 1;
}

int sufPref (char s1[], char s2[]) { //10 em 10
	int i, ii, j,c=0, m=0;
	for(i=0;s1[i]!='\0';i++) {
		ii=i;
		if (s1[i]==s2[0]) {
			for (j=0;s1[ii]!='\0' && s1[ii]==s2[j] && s2[j]!='\0';j++,ii++) c++;
		}
		if (s1[ii]!='\0') c=0;
		else {
			if (c>m) m=c;
		}
	}
	return m;
}

int questao22 () {
	char s[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%[^\n]", s);
	printf("A string tem %d palavras.\n", contaPal(s));
	return 1;
}

/*int i,c=1;
	if (s[0]=='\0') return 0;
	else {
		for (i=0; s[i+1]!='\0'; i++) {
			if (isspace(s[i]) && !isspace(s[i+1])) c++;
		}
	}
	return c; */

int contaPal (char s[]) { //10 de 10 (o isspace não está a funcionar corretamente)
   int i=0,c=0, marcador=0;
	while(s[i]!='\0') {
	   marcador = 0;
	   while((s[i]!='\0') && (s[i]==' ')) i++;
	   while((s[i]!='\0') && (s[i]!=' '))	{
	    	i++;
	    	marcador = 1;
	}
	if(marcador == 1) c++;
	}
	return c;
}

int questao23 () {
	char s[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s);
	printf("A string tem %d vogais.\n", contaVogais(s));
	return 1;
}

int contaVogais (char s[]) { //10 em 10
	int i, c=0;
	for (i=0; s[i]!='\0'; i++) {
		if (s[i]=='A' || s[i]=='a' || s[i]=='E' || s[i]=='e' || s[i]=='I' || s[i]=='i' || s[i]=='O' || s[i]=='o' || s[i]=='U' || s[i]=='u') c++;
	}
	return c;
}

int questao24 () {
	char a[MAXSIZE];
	char b[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", a);
	printf("Escreva a segunda string:\n");
	scanf("%s", b);
	if (contida(a,b)) printf("A primeira string está contida na segunda.\n");
	else printf("A primeira string não está contida na segunda.\n");
	return 1;
}

int contida (char a[], char b[]) { //10 em 10
	int i, j;
	for (i=0; a[i]!='\0';i++) {
		for(j=0;b[j]!='\0' && a[i]!=b[j];j++);
		if(b[j]=='\0') { return 0; break; }
	}
	return 1;
}

int questao25() {
	char s[MAXSIZE];
	printf("Escreva uma string:\n");
	scanf("%s", s);
	if (palindorome(s)) printf("A string é palindrome.\n");
	else printf("A string não é palindrome.\n");
	return 1;
}

int palindorome (char s[]) { //10 em 10
	int i, j=strlen(s);
	for(i=0; i!=j/2 && s[i]==s[j-i-1]; i++);
	return (i==j/2);
} 

int questao26 () {
	char x[MAXSIZE]; int d;
	printf("Escreva uma string:\n");
	scanf("%s",x);
	d=remRep(x);
	printf("A string sem repetidos é %s e tem tamanho %d.\n", x, d);
	return 1;
}

int remRep (char x[]) { //10 em 10
	int i, e=0;
	for(i=0; x[i]!='\0';i++) 
		if (x[i]!=x[i+1]) { 
			x[e]=x[i];
			e++; 
		}
	x[e]='\0';
	return e;
}

int questao27 () {
	char t[MAXSIZE]; int tam;
	printf("Escreva uma string:\n");
	scanf("%[^\n]", t);
	tam=limpaEspacos(t);
	printf("A string sem espaços repetidos é: %s. O seu tamanho é: %d.\n", t, tam);
	return 1;
}

int limpaEspacos (char t[]) { //10 em 10
	int i, e=0;
	for(i=0; t[i]!='\0';i++) {
		if (!isspace(t[i]) || !isspace(t[i+1])) {
			t[e]=t[i];
			e++;
		}
	}
	t[e]='\0';
	return e;
}

int questao28() {
	int v[MAXSIZE];
	int N;
	int x;
	int i;
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &N);
	printf("Escreva o array de inteiros(Um número de cada vez):\n");
	for(i=0;i<N;i++)
    scanf("%d", &v[i]);
	printf("Escreva o número que quer inserir:\n");
	scanf("%d", &x);
	insere(v, N, x);
	printf("O array com %d inserido é:\n", x);
	for(i=0;i<N+1;i++)
	printf("%d ", v[i]);
    printf("\n");
	return 1;
}

void insere (int v[], int N, int x) { //1 em 10, problema dos testes
	int i, l, j;
	for(i=0; i!=N && v[i]<=x; i++); 
	l=i; 
	if(v[i]>x) {
		for(j=N+1;j>i;j--) {
			v[j]=v[j-1];
		}
	}
	v[i]=x;	
}

int questao29 () {
	int r[MAXSIZE];
	int a[MAXSIZE];
	int b[MAXSIZE];
	int na, nb, i;
	printf("Escreva o tamanho do primeiro array:\n");
	scanf("%d", &na);
	printf("Escreva o tamanho do segundo array:\n");
	scanf("%d", &nb);
	printf("Escreva o primeiro array (um numero de cada vez)\n");
	for(i=0; i!=na;i++)
		scanf("%d", &a[i]);
	printf("Escreva o segundo array (um numero de cada vez)\n");
	for(i=0; i!=nb;i++)
		scanf("%d", &b[i]);
	for(i=0;i!=(na+nb); i++) r[i]=0;
	merge(r, a, b, na, nb);
	printf("O array ordenado é:\n");
	for(i=0; i!=(na+nb);i++)
		printf("%d ", r[i] );
	printf("\n");
	return 1;
}

void merge (int r[], int a[], int b[], int na, int nb) { // 0 em 10, problema nos testes
	int i,j=0,k=0;
	/*printf("array a, tamanho %d: ", na);   ****para ver os testes
	for(i=0;i<na;i++) printf("%d ", a[i]);
	printf("\n");
	printf("array b, tamanho %d: ", nb);
	for(i=0;i<na;i++) printf("%d ", b[i]);
	printf("\n");*/
	for (i=0;i!=na+nb && j<na && k<nb;i++) {
			if(a[j]<=b[k]) {
			r[i]=a[j]; j++;
			}
			else {
			r[i]=b[k]; k++;
			}
	}
	for(i;i!=na+nb;i++) {  /*caso um dos arrays tenha terminado, acaba de preencher r*/
		if (j==na && k!=nb) {
			r[i]=b[k]; k++;
		}
		if (j!=na && k==nb) {
			r[i]=a[j]; j++;
		}
	}
}

int questao30 () {
	int a[MAXSIZE], i, j, k, tam; 
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &tam);
	printf("Escreva o indice onde começar:\n");
	scanf("%d", &i);
	printf("Escreva o indice onde acabar:\n");
	scanf("%d", &j);
	printf("Escreva o array (um numero de cada vez):\n");
	for(k=0;k<tam;k++) {
		scanf("%d", &a[k]);
	}
	if(crescente(a,i,j)) {
		printf("O array é crescente entre %d e %d.\n",i, j );
	}
	else printf("O array não é crescente entre %d e %d.\n",i, j );
	return 1;
}

int crescente (int a[], int i, int j) { //10 em 10
	for(i;i<j;i++)
		if(a[i]>a[i+1]) return 0;
	return 1;
}

int questao31 () {
	int v[MAXSIZE], N, i, d;
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &N);
	printf("Escreva o array (um numero de cada vez):\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v[i]);
	}
	d=retiraNeg(v, N);
	printf("O array sem negativos tem tamanho %d e é:\n", d);
	for(i=0;i<d;i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
	return 1;
}

int retiraNeg (int v[], int N) { //10 em 10
	int i, e=0;
	for(i=0;i<N;i++)
		if (v[i]>=0) {
			v[e]=v[i];
			e++;
		}
	return e;
}

int questao32 () {
	int v[MAXSIZE], N, i;
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &N);
	printf("Escreva o array (um numero de cada vez):\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v[i]);
	}
	printf("O inteiro menos frequente é: %d.\n", menosFreq(v, N));
	return 1;
}

int menosFreq (int v[], int N) { //10 em 10
	int i, f=v[0], c=1, m;
	for(m=1; m<N-1 && v[m]==v[m+1];m++);
	i=m;
	while(i<N-1) {
		while (v[i]!=v[i+1]) i++;
		while (v[i]==v[i+1]) { c++; i++; }
		if(c<m) {
			m=c;
			f=v[i];
		}
		c=0;
	}
	return f;
}

int questao33 () {
	int v[MAXSIZE]; int N, i;
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &N);
	printf("Escreva o array:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v[i]);
	}
	printf("O int mais frequente é o %d.\n", maisFreq(v, N));
	return 1;
}

int maisFreq (int v[], int N) { //10 em 10
	int i, c=1, m=1; int f=v[0];
	for(i=0; (i-1)<N;i++) {
		if (v[i]!=v[i+1]) { if (c>m) { m=c; f=v[i]; c=1; } }
		if (v[i]==v[i+1]) c++;
	}
	return f;
}

int questao34 () {
	int v[MAXSIZE]; int N, i;
	printf("Escreva o tamanho do array.\n");
	scanf("%d", &N);
	printf("Escreva o array:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v[i]);
	}
	printf("O comprimento da maior sequencia crescente de elementos consecutivos é: %d.\n", maxCresc(v, N));
	return 1;
}

int maxCresc (int v[], int N) { //não está no codeboard
	int i, c=1, m=1;
	for (i=0;i-1<N; i++) {
		if (v[i+1]<v[i]) {
			if(c>m) {m=c; c=1;}
		}
		else c++;
	}
	return m;
}

int questao35 () {
	int v[MAXSIZE]; int n, i, d;
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &n);
	printf("Escreva o array:\n");
	for(i=0;i<n;i++) {
		scanf("%d", &v[i]);
	}
	d=elimRep(v, n);
	printf("O array fica com tamanho %d e é:\n", d);
	for(i=0;i<d;i++) {
		printf("%d ", v[i]);
		printf("\n");
	}
	return 1;
}

int elimRep (int v[], int n) {
	int i, j, k;
	for (i=0;i<n;i++) {
		for (j=i+1;j<n;j++) {
			if (v[i]==v[j]) {
				for(k=j+1;k<n;k++) {
					v[k-1]=v[k];
				}
				n--;
			}
		}
	}
	return n;
}

int questao36 () {
	int v[MAXSIZE]; int n, i, d;
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &n);
	printf("Escreva o array ordenado :\n");
	for(i=0;i<n;i++) {
		scanf("%d", &v[i]);
	}
	d=elimRepOrd(v, n);
	printf("O array fica com tamanho %d e é:\n", d);
	for(i=0;i<d;i++) {
		printf("%d ", v[i]);
		printf("\n");
	}
	return 1;
}

int elimRepOrd (int v[], int n) {
	int i, e=0;
	for(i=0;i<n;i++){
		if(v[i]!=v[i+1]) {v[e]=v[i]; e++;}
	}
	return e;
}

int questao37() {
	int a[MAXSIZE], b[MAXSIZE], na, nb, i;
	printf("Escreva o tamanho do array a:\n");
	scanf("%d", &na);
	printf("Escreva o tamanho do array b:\n");
	scanf("%d", &nb);
	printf("Escreva o array a ordenado :\n");
	for(i=0;i<na;i++) {
		scanf("%d", &a[i]);
	}
	printf("Escreva o array b ordenado :\n");
	for(i=0;i<nb;i++) {
		scanf("%d", &b[i]);
	}
	printf("Os arrays têm %d elementos em comum.\n", comunsOrd(a,na,b, nb));
	return 1;
}

int comunsOrd (int a[], int na, int b[], int nb) {
	int i, j=0, c=0;
	for(i=0;i<na;i++) {
		for(;j<nb && a[i]>b[j]; j++);
			if(a[i]==b[j]) c++;
	}
	return c;
}

int questao38() {
	int a[MAXSIZE], b[MAXSIZE], na, nb, i;
	printf("Escreva o tamanho do array a:\n");
	scanf("%d", &na);
	printf("Escreva o tamanho do array b:\n");
	scanf("%d", &nb);
	printf("Escreva o array a:\n");
	for(i=0;i<na;i++) {
		scanf("%d", &a[i]);
	}
	printf("Escreva o array b:\n");
	for(i=0;i<nb;i++) {
		scanf("%d", &b[i]);
	}
	printf("Os arrays têm %d elementos em comum.\n", comuns(a,na,b, nb));
	return 1;
}

int comuns (int a[] ,int na, int b[] ,int nb) {
	int aux[nb], i, j, k, c=0;
	for(i=0;i<nb;i++) aux[i]=b[i];
	for (i=0; i<na; i++) { 
		for (j=0;j<nb && a[i]!=aux[j];j++);
		if (a[i]==aux[j]) {
			for(k=j+1;k<nb;k++) {
				aux[k-1]=aux[k];
			}
			c++;
			nb--;
		}
	}
	return c;
}

int questao39() {
	int v[MAXSIZE], n, i;
	printf("Escreva o tamanho do array:\n");
	scanf("%d", &n);
	printf("Escreva o array:\n");
	for(i=0;i<n;i++) {
		scanf("%d", &v[i]);
	}
	printf("O indice do menor elemento é: %d.\n", minInd(v, n));
	return 1;
}
		
int minInd (int v[], int n) { //10 em 10
	int i, min=v[0], imin=0;
	for(i=1;i<n;i++) {
		if(v[i]<min) { min = v[i]; imin =i;}
	}
	return imin;
}

int questao40() {
	int v[MAXSIZE], Ac[MAXSIZE], N, i;
	printf("Qual o tamanho do array?\n");
	scanf("%d", &N);
	printf("Escreva o array:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v[i]);
	}
	somasAc(v, Ac, N);
	printf("O array com as somas acumuladas é:\n");
	for(i=0;i<N;i++) {
		printf("%d ", Ac[i]);
	}
	printf("\n");
	return 1;
}

void somasAc (int v[], int Ac [], int N) { //10 em 10
	int i, soma=0;
	for(i=0;i<N;i++) {
		soma+=v[i];
		Ac[i]=soma;
	}
}

int questao41() {
	int N, i, j;
	printf("Qual o tamanho do lado da matriz? (matriz quadrada)\n");
	scanf("%d", &N);
	int m[N][N];
	printf("Escreva a matriz (preenche por linhas):\n");
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++)
			scanf("%d", &m[i][j]);
	}
	if(triSup(N, m)) printf("A matriz é triangular superior.\n");
	else printf("A matriz nao é triangular superior.\n");
	return 1;
}

int triSup (int N, int m[N][N]) { //10 em 10
	int i, j;
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
		printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<N;i++) {
		for(j=0;j<i;j++) {
			if((m[i][j])!=0) {return 0; break;}
		}
	}
	return 1;
}

void transposta (int N, float m[N][N]) { //10 em 10
	int i, j; float aux[N][N];
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			aux[i][j]=m[i][j];
		}
	}
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			m[j][i]=aux[i][j];
		}
	}
}

int questao42() {
	int N, i, j;
	printf("Qual o tamanho do lado da matriz? (matriz quadrada)\n");
	scanf("%d", &N);
	float m[N][N];
	printf("Escreva a matriz (preenche por linhas):\n");
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++)
			scanf("%f", &m[i][j]);
	}
	transposta(N, m);
	printf("A matriz transposta é:\n");
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++)
			printf("%f ", m[i][j]);
		printf("\n");
	}
	return 1;
}

int questao43() {
	int N, M, i, j;
	printf("Qual o nº de linhas da matriz?\n");
	scanf("%d", &N);
	printf("Qual o nº de colunas da matriz?\n");
	scanf("%d", &M);
	int a[N][M];
	int b[N][M];
	printf("Escreva a matriz a (preenche por linhas):\n");
	for(i=0;i<N;i++) {
		for(j=0;j<M;j++)
			scanf("%d", &a[i][j]);
	}
	printf("Escreva a matriz b (preenche por linhas):\n");
	for(i=0;i<N;i++) {
		for(j=0;j<M;j++)
			scanf("%d", &b[i][j]);
	}
	addTo(N, M, a, b);
	printf("A matriz com as somas é:\n");
	for(i=0;i<N;i++) {
		for(j=0;j<M;j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	return 1;
}

void addTo (int N, int M, int a [N][M], int b[N][M]) { //10 em 10
	int i, j;
	for(i=0; i<N;i++) {
		for(j=0;j<M;j++) 
			a[i][j]+=b[i][j];
	}
}

int questao44() {
	int N, i, j;
	printf("Qual o tamanho do lado da matriz? (matriz quadrada)\n");
	scanf("%d", &N);
	int m[N][N];
	printf("Escreva a matriz (preenche por linhas):\n");
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++)
			scanf("%d", &m[i][j]);
	}
	sumDiag(N, m);
	printf("A matriz transposta é:\n");
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++)
			printf("%d ", m[i][j]);
		printf("\n");
	}
	return 1;
}

void sumDiag (int N, int m [N][N]) { //10 em 10
	int i, j, soma;
	for(i=0;i<N;i++) {
		soma=0;
		for(j=0;j<N;j++) {
			if(i!=j) soma+=m[i][j];
		}
		m[i][i]=soma;
	}
}

int questao45() {
	char c='A';
 	while (c<='Z' || c<='z') {
  		printf ("%c - %d \n", c,c);
  		if (c=='Z') c='a';
  		else c++;
	}
	return 1;
}

int questao46() {
	int N, i;
	printf("Qual o tamanho dos Sets?\n");
	scanf("%d", &N);
	int v1[N], v2[N], r[N];
	printf("Escreva o primeiro set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v1[i]);
	} 
	printf("Escreva o segundo set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v2[i]);
	} 
	unionSet(N, v1, v2, r);
	printf("A união é:\n");
	for(i=0;i<N;i++)
		printf("%d ", r[i]);
	printf("\n");
	return 1;
}

int unionSet (int N, int v1[N], int v2[N], int r[N]) { //10 em 10
	int i;
	for(i=0; i<N;i++) r[i]=0;
	for(i=0; i<N;i++)
		if(v1[i]==1||v2[i]==1) r[i]=1;
	return 1;
}

int questao47() {
	int N, i;
	printf("Qual o tamanho dos Sets?\n");
	scanf("%d", &N);
	int v1[N], v2[N], r[N];
	printf("Escreva o primeiro set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v1[i]);
	} 
	printf("Escreva o segundo set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v2[i]);
	} 
	intersectSet(N, v1, v2, r);
	printf("A interseção é:\n");
	for(i=0;i<N;i++)
		printf("%d ", r[i]);
	printf("\n");
	return 1;
}

int intersectSet (int N, int v1[N], int v2[N], int r[N]) { //10 em 10
	int i;
	for(i=0; i<N;i++) r[i]=0;
	for(i=0; i<N;i++)
		if(v1[i]==1 && v2[i]==1) r[i]=1;
	return 1;
}

int questao48() {
	int N, i;
	printf("Qual o tamanho dos MSets?\n");
	scanf("%d", &N);
	int v1[N], v2[N], r[N];
	printf("Escreva o primeiro set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v1[i]);
	} 
	printf("Escreva o segundo set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v2[i]);
	} 
	intersectMSet(N, v1, v2, r);
	printf("A interseção é:\n");
	for(i=0;i<N;i++)
		printf("%d ", r[i]);
	printf("\n");
	return 1;
}

int intersectMSet (int N, int v1[N], int v2[N], int r[N]){ //10 em 10
	int i;
	for(i=0; i<N;i++) r[i]=0;
	for(i=0; i<N;i++) {
		if(v1[i]<v2[i]) r[i]=v1[i];
		else r[i]=v2[i];
	}
	return 1;
}

int questao49() {
	int N, i;
	printf("Qual o tamanho dos MSets?\n");
	scanf("%d", &N);
	int v1[N], v2[N], r[N];
	printf("Escreva o primeiro set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v1[i]);
	} 
	printf("Escreva o segundo set:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v2[i]);
	} 
	unionMSet(N, v1, v2, r);
	printf("A união é:\n");
	for(i=0;i<N;i++)
		printf("%d ", r[i]);
	printf("\n");
	return 1;
}

int unionMSet (int N, int v1[N], int v2[N], int r[N]) { //10 em 10
	int i;
	for(i=0; i<N;i++) r[i]=0;
	for(i=0; i<N;i++) {
		if(v1[i]<v2[i]) r[i]=v2[i];
		else r[i]=v1[i];
	}
	return 1;
}

int questao50() {
	int N, i;
	printf("Qual o tamanho dos MSets?\n");
	scanf("%d", &N);
	int v[N];
	printf("Escreva o Mset:\n");
	for(i=0;i<N;i++) {
		scanf("%d", &v[i]);
	} 
	cardinalMSet(N, v);
	printf("O MSet tem %d elementos.\n", cardinalMSet(N, v));
	return 1;
}

int cardinalMSet (int N, int v[N]) { //10 em 10
	int i, s=0;
	for(i=0;i<N;i++)
		s+=v[i];
	return s;
}

int interpretar (char *linha) {
	char cmd [MAXSIZE];
	char arg1 [MAXSIZE];
	char arg2 [MAXSIZE];
	int args;
	args = sscanf (linha, "%s %s %s", cmd, arg1, arg2); /*cmd conta como arg*/
	if (strcmp (cmd, "questao1") == 0 && args == 1) {
		return questao1 ();
	}
	if (strcmp (cmd, "questao2") == 0 && args == 1) {
		return questao2 ();
	}
	if (strcmp (cmd, "questao3") == 0 && args == 1) {
		return questao3 ();
	}
	if (strcmp (cmd, "questao4") == 0 && args == 1) {
		return questao4 ();
	}
	if (strcmp (cmd, "questao5") == 0 && args == 1) {
		return questao5 ();
	}
	if (strcmp (cmd, "questao6") == 0 && args == 1) {
		return questao6 ();
	}
	if (strcmp (cmd, "questao7") == 0 && args == 1) {
		return questao7 ();
	}
	if (strcmp (cmd, "questao8") == 0 && args == 1) {
		return questao8 ();
	}
	if (strcmp (cmd, "questao9") == 0 && args == 1) {
		return questao9 ();
	}
	if (strcmp (cmd, "questao10") == 0 && args == 1) {
		return questao10 ();
	}
	if (strcmp (cmd, "questao11") == 0 && args == 1) {
		return questao11 ();
	}
	if (strcmp (cmd, "questao12") == 0 && args == 1) {
		return questao12 ();
	}
	if (strcmp (cmd, "questao13") == 0 && args == 1) {
		return questao13 ();
	}
	if (strcmp (cmd, "questao14") == 0 && args == 1) {
		return questao14 ();
	}
	if (strcmp (cmd, "questao15") == 0 && args == 1) {
		return questao15 ();
	}
	if (strcmp (cmd, "questao16") == 0 && args == 1) {
		return questao16 ();
	}
	if (strcmp (cmd, "questao17") == 0 && args == 1) {
		return questao17 ();
	}
	if (strcmp (cmd, "questao18") == 0 && args == 1) {
		return questao18 ();
	}
	if (strcmp (cmd, "questao19") == 0 && args == 1) {
		return questao19 ();
	}
	if (strcmp (cmd, "questao20") == 0 && args == 1) {
		return questao20 ();
	}
	if (strcmp (cmd, "questao21") == 0 && args == 1) {
		return questao21 ();
	}
	if (strcmp (cmd, "questao22") == 0 && args == 1) {
		return questao22 ();
	}
	if (strcmp (cmd, "questao23") == 0 && args == 1) {
		return questao23 ();
	}
	if (strcmp (cmd, "questao24") == 0 && args == 1) {
		return questao24 ();
	}
	if (strcmp (cmd, "questao25") == 0 && args == 1) {
		return questao25 ();
	}
	if (strcmp (cmd, "questao26") == 0 && args == 1) {
		return questao26 ();
	}
	if (strcmp (cmd, "questao27") == 0 && args == 1) {
		return questao27 ();
	}
	if (strcmp (cmd, "questao28") == 0 && args == 1) {
		return questao28 ();
	}
	if (strcmp (cmd, "questao29") == 0 && args == 1) {
		return questao29 ();
	}
	if (strcmp (cmd, "questao30") == 0 && args == 1) {
		return questao30 ();
	}
	if (strcmp (cmd, "questao31") == 0 && args == 1) {
		return questao31 ();
	}
	if (strcmp (cmd, "questao32") == 0 && args == 1) {
		return questao32 ();
	}
	if (strcmp (cmd, "questao33") == 0 && args == 1) {
		return questao33 ();
	}
	if (strcmp (cmd, "questao34") == 0 && args == 1) {
		return questao34 ();
	}
	if (strcmp (cmd, "questao35") == 0 && args == 1) {
		return questao35 ();
	}
	if (strcmp (cmd, "questao36") == 0 && args == 1) {
		return questao36 ();
	}
	if (strcmp (cmd, "questao37") == 0 && args == 1) {
		return questao37 ();
	}
	if (strcmp (cmd, "questao38") == 0 && args == 1) {
		return questao38 ();
	}
	if (strcmp (cmd, "questao39") == 0 && args == 1) {
		return questao39 ();
	}
	if (strcmp (cmd, "questao40") == 0 && args == 1) {
		return questao40 ();
	}
	if (strcmp (cmd, "questao41") == 0 && args == 1) {
		return questao41 ();
	}
	if (strcmp (cmd, "questao42") == 0 && args == 1) {
		return questao42 ();
	}
	if (strcmp (cmd, "questao43") == 0 && args == 1) {
		return questao43 ();
	}
	if (strcmp (cmd, "questao44") == 0 && args == 1) {
		return questao44 ();
	}
	if (strcmp (cmd, "questao45") == 0 && args == 1) {
		return questao45 ();
	}
	if (strcmp (cmd, "questao46") == 0 && args == 1) {
		return questao46 ();
	}
	if (strcmp (cmd, "questao47") == 0 && args == 1) {
		return questao47 ();
	}
	if (strcmp (cmd, "questao48") == 0 && args == 1) {
		return questao48 ();
	}
	if (strcmp (cmd, "questao49") == 0 && args == 1) {
		return questao49 ();
	}
	if (strcmp (cmd, "questao50") == 0 && args == 1) {
		return questao50 ();
	}
	else if (strcmp (cmd, "sair") == 0) { 
		return 0;
		}
		else {
			printf("Comando inválido!!\n"); 
			return -1;
		}
}

void interpretador () {
	int resultado = 0;
	char *leitura = NULL;
	char buffer [MAXSIZE];
	int ciclo = 1;
	printf("Selecione a questão escrevendo \"questaon\", onde n é o número da questão. \"sair\" para terminar o programa.\n");
	while (ciclo) {
		leitura = fgets (buffer, MAXSIZE, stdin);
		if (leitura!=NULL) {
			resultado = interpretar (buffer);
			if (resultado==0) ciclo = 0; else ciclo = 1;
			if (resultado==2 || resultado == 1) {
				printf("escolha nova questao\n");
			    fgets(buffer, MAXSIZE, stdin);
			}
		}
	}
}

int main () {
	interpretador ();
	return 0;
}