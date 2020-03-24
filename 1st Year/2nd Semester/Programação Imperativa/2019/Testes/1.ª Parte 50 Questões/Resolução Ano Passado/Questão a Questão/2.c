#include<stdio.h>



int main(){
  int total, n, a;
  total = a = 0;

  do {
    scanf(" %d", &n);
    total += n;
    ++a;
  } while(n != 0);

  printf("%f\n", ((float)total)/(a-1));


}
