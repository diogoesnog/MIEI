#include<stdio.h>

typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;

typedef struct posicao {
  int x, y;
} Posicao;


Posicao posFinal (Posicao inicial, Movimento mov[], int N){

  for(int i = 0; i < N; i++){
    switch(mov[i]){
      case Norte: inicial.y++;
                  break;
      case Sul:   inicial.y--;
                  break;
      case Este:  inicial.x++;
                  break;
      case Oeste: inicial.x--;
                  break;
    }
  }
  return inicial;
}



int main(){

  Movimento mov[1000] = {Norte, Norte, Este, Sul, Oeste, Norte, Sul, Este, Este};

  Posicao inicial;
  inicial.x = 0;
  inicial.y = 0;

  inicial = posFinal(inicial, mov, 9);

  printf("x = %d\ny = %d\n\n", inicial.x, inicial.y);

  return 0;
}
