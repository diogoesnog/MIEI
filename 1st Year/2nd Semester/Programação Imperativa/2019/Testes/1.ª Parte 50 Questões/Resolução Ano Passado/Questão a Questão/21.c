#include<stdio.h>


int vogal (char c){

  char vogais[10] = {'a','e','i','o','u','A','E','I','O','U'};

  int i = 0;
  while (c != vogais[i] && i < 10){
    i++;
  }
  if (i == 10) return 0;
  else return 1;

}

int contaVogais (char s[]){

  int i = 0;
  int conta = 0;
  while (s[i] != '\0'){
    if (vogal(s[i])) conta++;
    i++;
  }

  return conta;
}



int main(){

  char s[1000];

  int n = 1;
  while (n) {

  printf("String para analisar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("%d\n\n", contaVogais(s));
  }
}
