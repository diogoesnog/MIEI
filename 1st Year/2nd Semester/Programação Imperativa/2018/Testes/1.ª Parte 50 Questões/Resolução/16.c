#include<stdio.h>


int difConsecutivos (char s[]){

  int maior = 0;
  int current = 1;

  for(int i = 0; s[i] != '\0'; i++){

    if (s[i+1] != s[i] && s[i+1] != '\0'){
      current++;
    }
    else {
      if (current > maior) {
        maior = current;
      }
      current = 1;
    }



  }
  return maior;
}



int main(){

  char s[1000];

  int n = 1;
  while (n) {

  printf("String para analisar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("%d\n\n", difConsecutivos(s));
  }
}
