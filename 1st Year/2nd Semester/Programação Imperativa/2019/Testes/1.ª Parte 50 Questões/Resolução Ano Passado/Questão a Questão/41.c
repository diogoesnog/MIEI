#include<stdio.h>


void addTo (int N, int M, int a [N][M], int b[N][M]){

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      a[i][j] += b[i][j];
    }
  }
}


int main(){

  int v[5][5] = {{1,2,3,4,5},
                 {0,1,2,3,4},
                 {0,0,1,2,3},
                 {0,0,0,1,2},
                 {0,0,0,0,1}};

  int v2[5][5] = {{1,2,3,4,5},
                  {0,1,2,3,0},
                  {4,0,1,6,3},
                  {0,3,9,1,0},
                  {1,0,5,0,1}};


  addTo(5, 5, v, v2);

  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      printf("%d ", v[i][j]);//numero de casa decimais
    }
    printf("\n");
  }

  return 0;
}
