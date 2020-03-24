#include<stdio.h>


void transposta (int N, float m [N][N]){

  float aux[N][N];
  int a;

  for(int i = 0; i < N; i++){
    for(a = 0; a < N; a++){
      aux[a][i] = m[i][a];
    }
  }

  for(int i = 0; i < N; i++){
    for(a = 0; a < N; a++){
      m[i][a] = aux[i][a];
    }
  }
}


int main(){

  float v[5][5] = {{1,2,3,4,5},
                   {0,1,2,3,4},
                   {0,0,1,2,3},
                   {0,0,0,1,2},
                   {0,0,0,0,1}};

  float v2[5][5] = {{1,2,3,4,5},
                    {0,1,2,3,0},
                    {4,0,1,6,3},
                    {0,3,9,1,0},
                    {1,0,5,0,1}};

  transposta(5,v);
  transposta(5,v2);

  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      printf("%.0f ", v[i][j]);//numero de casa decimais
    }
    printf("\n");
  }

  printf("\n\n\n");

  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      printf("%.0f ", v[i][j]);
    }
    printf("\n");
  }

  return 0;
}
