#include<stdio.h>
#include<string.h>

void mystrrev (char s[]){

  char troca;
  int l = strlen(s);

  for(int i = 0; i < l/2; i++){
    troca = s[i];
    s[i] = s[l-i-1];
    s[l-i-1] = troca;
  }

}



int main(){

  char s[100];

  int n = 1;
  while (n) {

  printf("String para reverter: \n");
  scanf("%[^\n]", s);//isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();
  mystrrev(s);

  printf("%s\n\n", s);

  }
}
