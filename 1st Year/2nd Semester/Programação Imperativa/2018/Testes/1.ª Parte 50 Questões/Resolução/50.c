#include<stdio.h>
#include<stdlib.h>

typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;

typedef struct posicao {
  int x, y;
} Posicao;


int vizinhos (Posicao p, Posicao pos[], int N){
  int conta = 0;

  for(int i = 0; i < N; i++){
    if (abs(p.x - pos[i].x) + abs(p.y - pos[i].y) == 1){
      conta++;
    }
  }
  return conta;
}



int main(){



  Posicao p0;
  p0.x = 0;
  p0.y = 0;

  Posicao p1;
  p1.x = 0;
  p1.y = 1;

  Posicao p2;
  p2.x = 1;
  p2.y = 1;

  Posicao p3;
  p3.x = 2;
  p3.y = 0;

  Posicao p4;
  p4.x = 3;
  p4.y = 5;

  Posicao pos[1000] = {p1, p2, p3, p4};

  printf("%d\n\n", vizinhos(p0, pos, 4));

  return 0;
}
