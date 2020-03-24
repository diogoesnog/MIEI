#include<stdio.h>
#include<ctype.h>
#include<string.h>

void truncW (char s[], int n){

  char aux[1000];
  int i = 0;
  int paux = 0;
  int current = 0;

  while(s[i] != '\0'){

    if (isspace(s[i])) {
      current = 0;
      aux[paux] = ' ';
      paux++;
    }
    else if (current < n){
      aux[paux] = s[i];
      current++;
      paux++;
    }
    i++;
  }

  aux[paux] = '\0';

  strcpy(s, aux);
}


int main(){

  char s[1000];
  int i;

  int n = 1;
  while (n) {

  printf("String para truncar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("Queres truncar a quantas letras: ");
  scanf("\n%d", &i);
  truncW(s, i);

  printf("%s\n\n", s);
  }

}
