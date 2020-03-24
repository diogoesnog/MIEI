#include<stdio.h>

char *strcat(char s1[], char s2[]){

  int i = 0;
  while(s1[i] != '\0'){
  ++i;
  }

  int j = 0;
  while(s2[j] != '\0'){
    s1[i+j] = s2[j];
    j++;
  }

  s1[i+j] = '\0';

  return s1;
}

int main(){

  char s1[100];
  char s2[100];

  int n = 1;
  while (n) {


  printf("Que strings?\n");


  scanf("\n%[^\n]", s1);//isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  scanf("\n%[^\n]", s2);
  getchar();

  strcat(s1 ,s2);

  printf("%s\n", s1);

  }

}
