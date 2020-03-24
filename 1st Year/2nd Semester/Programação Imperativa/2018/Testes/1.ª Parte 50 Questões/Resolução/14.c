#include<stdio.h>


char charMaisfreq (char s[]){

  if (s[0] == '\0') return 0;

  char mf;
  int n = 0;

  char temp;
  int conta;

  for(int i = 0; s[i] != '\0'; i++){
    temp = s[i];
    conta = 0;

    for(int j = 0; s[j] != '\0'; j++){
      if (s[j] == temp) conta++;
    }

    if (conta > n){
      mf = temp;
      n = conta;
    }

  }

  return mf;
}




int main(){

  char s[1000];

  int n = 1;
  while (n) {

  printf("String para analisar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("%c\n\n", charMaisfreq(s));
  }
}
