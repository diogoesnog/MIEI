#include<stdio.h>


int strcmp (char s1[], char s2[]){

  int i = 0;

  while(s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'){ //aqui só é preciso verificar se um deles acabou mas deixei os dois por uma questão de legibilidade)
    i++;
  }

  return (s1[i]-s2[i]);

}


int main(){

  char s1[100];
  char s2[100];

  int n = 1;
  while (n) {

  printf("Duas strings se faz favor: \n");
//isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  scanf("%[^\n]", s1);
  getchar();
  scanf("%[^\n]", s2);
  getchar();

  printf("%d\n\n", strcmp(s1, s2));

  }
}
