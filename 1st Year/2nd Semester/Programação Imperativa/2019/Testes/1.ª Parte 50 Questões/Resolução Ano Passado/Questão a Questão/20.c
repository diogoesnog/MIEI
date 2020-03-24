#include<stdio.h>
#include<ctype.h>

int contaPal (char s[]){

  int conta = 0;

  if(s[0] != '\0') conta++;

  int i = 0;
  while (isspace(s[i]) != 0){
    i++;
  }

  while (s[i] != '\0') {
    if (isspace(s[i]) != 0 && isspace(s[i-1]) == 0) conta++;
    i++;
  }



  if (isspace (s[i-1]) != 0){
    conta--;
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

  printf("%d\n\n", contaPal(s));
  }
}
