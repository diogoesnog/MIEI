#include<stdio.h>

int sufPref (char s1[], char s2[]){

  int last = 0;
  while (s1[last] != '\0'){
    last++;
  }
  last--;



  int maiorAtual = 0;
  int a = 0;
  while (s2[a] != '\0'){
    if(s1[last] == s2[a]){
      int i = 1;
      while(s1[last-i] == s2[a-i] && a-i >= 0 && last-i >= 0){
        i++;
      }
      if (i > maiorAtual) maiorAtual = i;

    }
    a++;
  }

  return maiorAtual;
}

//esta tá meia complicada... Eu procuro na segunda string um char que seja igual ao ultimo da primeira, e depois ando para trás nas duas até elas serem difirentes.


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

  printf("%d\n\n", sufPref(s1, s2));

  }
}
