#include<stdio.h>
#include<ctype.h>
#include<string.h>




int limpaEspacos (char s[]){

  char aux[strlen(s)];

  int paux = 0;
  for(int i = 0; s[i] != '\0'; i++){
    if (s[i] != ' '){
      aux[paux++] = s[i];
    }
    else if (s[i-1] != ' ') aux[paux++] = s[i];
  }

  aux[paux] = '\0';

  strcpy(s,aux);

  return paux;
}



int main(){

  char s[1000];

  int n = 1;
  while (n) {

  printf("String para analisar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("A string tem agora %d letras", limpaEspacos(s));
  printf(" e é \"%s\"\n\n", s);
  }
}
