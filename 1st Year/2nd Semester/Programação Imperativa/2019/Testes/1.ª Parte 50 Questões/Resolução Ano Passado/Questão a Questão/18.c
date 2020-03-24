#include<stdio.h>



int maiorSufixo (char s1 [], char s2 []){

  int i = 0;
  while(s1[i] != '\0'){
    i++;
  }

  int j = 0;
  while(s2[j] != '\0'){
    j++;
  }

  i--; j--;
  int conta = 0;
  while (i >= 0 && j >= 0 && s1[i] == s2[j]){
    conta++;
    j--;
    i--;
  }

  return conta;
}





int main(){

  char s1[100];
  char s2[100];


  int n = 1;
  while (n) {

  printf("Duas strings se faz favor: \n");
//isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  scanf("\n%[^\n]", s1);
  getchar();
  scanf("\n%[^\n]", s2);
  getchar();

  printf("%d\n\n", maiorSufixo(s1, s2));

  }
}
