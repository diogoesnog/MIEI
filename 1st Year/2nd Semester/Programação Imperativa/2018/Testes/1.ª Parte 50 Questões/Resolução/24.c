#include<stdio.h>
#include<string.h>


int remRep (char s[]){

  char aux[strlen(s)];

  int i = 0;
  int paux = 0;
  while(s[i] != '\0'){

  if (s[i+1] != s[i]){
    aux[paux++] = s[i];
  }
  i++;


  }
  aux[paux] = '\0';

  strcpy(s, aux);
  return paux;
}



int main(){

  char s[1000];

  int n = 1;
  while (n) {

  printf("String para analisar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("A string tem agora %d letras", remRep(s));
  printf(" e é \"%s\"\n\n", s);
  }
}
