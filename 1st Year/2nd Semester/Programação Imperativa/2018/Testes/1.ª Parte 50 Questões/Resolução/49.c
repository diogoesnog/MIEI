#include<stdio.h>
#include<stdlib.h>

typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;

typedef struct posicao {
  int x, y;
} Posicao;


int maisCentral (Posicao pos[], int N){
  int ind = 0;
  int minDist = abs(pos[0].x) + abs(pos[0].y);
  int test;

  for(int i = 1; i < N; i++){
    test = abs(pos[i].x) + abs(pos[i].y);
    if (test < minDist){
      minDist = test;
      ind = i;
    }
  }
  return ind;
}



int main(){



  Posicao p0;
  p0.x = 4;
  p0.y = 3;

  Posicao p1;
  p1.x = 1;
  p1.y = 2;

  Posicao p2;
  p2.x = 10;
  p2.y = 0;

  Posicao p3;
  p3.x = 1;
  p3.y = 6;

  Posicao p4;
  p4.x = 2;
  p4.y = 5;

  Posicao pos[1000] = {p0, p1, p2, p3, p4};

  printf("O mais central é o %d\n\n", maisCentral(pos, 5));

  return 0;
}
