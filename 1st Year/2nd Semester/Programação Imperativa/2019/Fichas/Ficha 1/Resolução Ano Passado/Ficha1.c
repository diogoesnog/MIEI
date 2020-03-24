#include <stdio.h>

// Resolução da Ficha nº.1

// (1) Estado e Atribuições
// (1)
int x, y;
x = 3; y = x+1;
x = x*y; y = x+y;
printf("%d %d\n", x, y);

/* Este excerto inicia o x a 3 e o y a 4. Após isso, o x passa a ser 12 (3*4) e o y passa a ser 16 (12+4).
Por fim, imprime estes resultados. */

// (2)
int main ()  {
int x, y;
x = 0;
printf("%d %d\n", x, y);
}

/* Como o y não é um valor inicializado como o x, o compilador vai inicializá-lo a 0, assim como fizemos com o x.
Assim sendo, vai imprimir estes dois valores dando como output dois valores a 0. */

// (3)
char a, b, c;
a = 'A'; b = ' '; c = '0';
printf("%c %d\n", a, a);
a = a+1, c = c+2
printf("%c %d %c %d\n", a, a, c, c);
c = a+b;
printf("%c %d\n", c, c);

/* Apenas necessitamos de saber que um caractér tem o seu valor em modo constante e em modo double. Neste excerto
apenas estamos a jogar com isso, aumentando determinados valores e imprimindo o que pretendemos ver como output. */

// (4)
int x , y;
x = 200; y = 100;
x = x+y; y = x-y; x = x-y;
printf("%d %d\n", x, y);

/* Aumentos o valor de x para 300, depois o valor de y passará a ser o valor de x anteriormente atualizado menos o seu 
valor mais recente e, por fim, o valor do x modificará novamente. Resta apenas imprimir os valores como output. */

// (5)
int x, y;
x = 100; y = 28;
x += y ; y -= x;
printf("%d %d\n", x++, ++y);
printf("%d %d\n", x, y);

/* A única parte importante aqui a reter são os incrementos do inteiro x e y. Quando fazemos "x++" estamos a incrementar
o valor do x para a próxima vez que o x for usado. Quando fazemos "++y" estamos a incrementar o valor do y para a linha do código 
em questão. Ou seja, o nosso "x++" implica que no próximo printf o valor do x se encontra aumentado em uma unidade enquanto que
o "++y" implica que o valor do y se encontre aumentado em uma unidade no printf em questão. */

// (2) Estruturas de Controlo

// (1)

// (a)
int x , y;
x = 3; y = 5;
if (x > y)
y = 6;
printf("%d %d\n", x, y);

/* Como o x não é maior que o y, obtemos como output o valor do x a 3 e o valor do y a 5. */

// (b)
int x, y;
x = y = 0;
while (x != 11) {
x = x+1; y += x;
}
printf("%d %d\n", x, y);

/* Enquanto o valor do x for diferente de 11, vamos sempre aumentando uma unidade ao x e somando o valor do y
atual com o valor do x atual. Assim sendo, obtemos como output o valor do x a 11 e o valor do y a 66. */

// (c)
int x, y;
x = y = 0;
while (x != 11) {
x = x+2; y += x;
}
printf("%d %d\n", x, y);

/* Funciona igual ao excerto anterior. A única diferença está no aumento do valor de x. */

// (2)
void linhas (int n) {
 while (n>0) {
  putchar('#');
  n=n-1;
}
 putchar('\n');
}
 
void quadrados (int n) {
 int i;
 for (i=0; i<n; i++)
  linhas (n);
}
 
int main () {
 quadrados(5);
 return 0;
}