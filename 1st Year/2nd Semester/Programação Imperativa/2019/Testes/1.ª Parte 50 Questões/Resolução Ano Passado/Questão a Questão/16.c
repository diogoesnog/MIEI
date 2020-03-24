#include<stdio.h>


int difConsecutivos (char s[]){

  int maior = 0;
  int current = 1;

  for(int i = 0; s[i] != '\0'; i++){

    if (s[i+1] != s[i] && s[i+1] != '\0'){
      current++;
    }
    else {
      if (current > maior) {
        maior = current;
      }
      current = 1;
    }



  }
  return maior;
}



int main(){

  char s[1000];

  int n = 1;
  while (n) {

  printf("String para analisar: \n");
  scanf("\n%[^\n]", s); //isto lê do teclado até encontrar o caracter depois do ^, neste caso, o enter.
  getchar();

  printf("%d\n\n", difConsecutivos(s));
  }
}




int auxDif (char s[]){
    
    int i = 0;
    int res = 0;
    
    while(s[i]!='\0'){

      if(temRepetidos(s, i+1) == 0) res = i + 1;
      i++;
    }

    return res;
}

int temrepetidos (char s[], int N){
    int i,j,r = 0;
    
    for (i = 0; s[i] != '\0' && !r && i < N;i++)
        for (j = 0; s[j] != '\0' && !r && j < N;j++)
            if (i!=j && s[i] == s[j])
                r = 1;
    
    return r;
}

int difConsecutivos(char s[]) {
 
  int i = 0;
  int res = 0;
    
  int aux;

  while(s[i]!='\0'){

    aux = auxDif(s+i);
    if (aux > res) res = aux;

    i++;
  }
 
  return res;  
}