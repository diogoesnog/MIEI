#include<stdio.h>

void strnoV (char s[]){


  for (int i = 0; s[i]; i++) {
    if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U'){
      for(int j = i; s[j] != '\0'; j++){
        s[j] = s[j+1];
      }
      i--;
    }
  }
}



int main(){


  char s[100];

  int n = 1;
  while (n) {

  printf("String para tirar as vogais: \n");
  scanf("%[^\n]", s);//isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();
  strnoV(s);

  printf("%s\n\n", s);


  }
}
