#include<stdio.h>
#include<string.h>


int palindroma (char s[]){

  int l = strlen(s);
  if (l > 0) l--;

  for(int i = 0; i < l-i; i++){
    if (s[i] != s[l-i]) return 0;
  }

  return 1;
}



int main(){

  char s[1000];

  int n = 1;
  while (n) {

  printf("String para analisar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("%d\n\n", palindroma(s));
  }
}
