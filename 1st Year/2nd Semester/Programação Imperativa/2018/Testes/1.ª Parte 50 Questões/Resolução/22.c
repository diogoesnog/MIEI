#include<stdio.h>


int contem(char c, char s[]){

  for(int i = 0; s[i] != '\0'; i++){
    if (c == s[i]) return 1;
  }

  return 0;
}



int contida (char s1[], char s2[]){

  int i = 0;
  while(s1[i] != '\0'){
    if (contem(s1[i],s2)) i++;
    else return 0;
  }

  return 1;
}



int main(){

  char s1[1000];
  char s2[1000];

  int n = 1;
  while (n) {

  printf("Duas strings se faz o obséquio: \n");
  scanf("\n%[^\n]", s1); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();
  scanf("\n%[^\n]", s2);
  getchar();


  if(contida(s1,s2)) printf("Verdadeiro\n\n");
  else printf("Falso\n\n");


  }
}
