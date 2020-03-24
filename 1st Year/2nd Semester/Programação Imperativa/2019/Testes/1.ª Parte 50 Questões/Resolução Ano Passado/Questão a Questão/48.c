#include<stdio.h>

typedef enum movimento {Norte = 'N',
                       Oeste = 'O',
                       Sul = 'S',
                       Este = 'E'} Movimento;

typedef struct posicao {
  int x, y;
} Posicao;


int caminho (Posicao inicial, Posicao final, Movimento mov[], int N){
  int i = 0;

  while(i < N && inicial.x != final.x){
    if(inicial.x < final.x){
      mov[i++] = Este;
      inicial.x++;
    }
    else if(inicial.x > final.x){
      mov[i++] = Oeste;
      inicial.x--;
    }
  }

  while (i < N && inicial.y != final.y) {
    if(inicial.y < final.y){
      mov[i++] = Norte;
      inicial.y++;
    }
    else if(inicial.y > final.y){
      mov[i++] = Sul;
      inicial.y--;
    }
  }

  if (inicial.x == final.x && inicial.y == final.y) return i;
  else return -1;

}


int main(){

  Movimento mov[1000];

  Posicao inicial;
  inicial.x = 0;
  inicial.y = 0;

  Posicao final;
  final.x = 4;
  final.y = 3;

  int tamMax = 10;


  int len = caminho(inicial, final, mov, tamMax);
  if (len >= 0){
    printf("O caminho tem %d passos e correponde a: ", len);
    for(int i = 0; i < len; i++){
      printf("%c ", (char)mov[i]);
    }
  }
  else printf("Num dá pah.\n");

  return 0;
}
