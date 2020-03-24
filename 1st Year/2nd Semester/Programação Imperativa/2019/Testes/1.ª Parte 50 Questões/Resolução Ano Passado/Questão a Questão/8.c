#include<stdio.h>

char *strcpy (char *dest, char source[]){

  int i = 0;
  while(source[i] != '\0'){
    dest[i] = source[i];
    i++;
  }
  dest[i] = '\0';
}


int main(){

  char source[100];
  char destination[100];

  int n = 1;
  while (n) {

  printf("Que string?\n");

//isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  scanf("%[^\n]", source);
  getchar();

  strcpy(destination ,source);

  printf("%s\n", destination);

  }

}
