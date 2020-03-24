#include<stdio.h>



char *strstr (char s1[], char s2[]){


  for(int i = 0; s1[i] != '\0'; i++){
    int j = 0;

    if(s1[0] == '\0' && s2[0] == '\0') return s1;

    if (s1[i] == s2[0]){
      //for(int j = 0; s2[j] != '\0' && s1[i+j] == s2[j]; j++)

      while(s2[j] != '\0' && s1[i+j] == s2[j]){
        j++;
      }
    }

    if (s2[j] == '\0') return (s1+i);
  }

  return NULL;
}



int main(){

  char s1[100];
  char s2[100];


  int n = 1;
  while (n) {

  printf("Duas strings se faz favor: \n");
//isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  scanf("%[^\n]", s1);
  scanf("%[^\n]", s2);

  printf("%s\n\n", strstr(s1, s2));

  }
}
