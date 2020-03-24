#include<stdio.h>


int triSup (int N, float m [N][N]){

  for(int i = 0; i < N; i++){
    for(int j = 0; j < i; j++){
      if (m[i][j] != 0) return 0;
    }
  }
  return 1;
}



int main(){

  float v[5][5] = {{1,2,3,4,5},
             {0,1,2,3,4},
             {0,0,1,2,3},
             {0,0,0,1,2},
             {0,0,0,0,1}};

  float v2[5][5] = {{1,2,3,4,5},
             {0,1,2,3,4},
             {0,0,1,2,3},
             {0,3,0,1,2},
             {0,0,0,0,1}};

printf("%d %d\n", triSup(5,v), triSup(5,v2));

  return 0;
}
