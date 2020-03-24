#include<stdio.h>


int qDig (unsigned int n){

  int r = 1;
  int i = 10;

  while (n >= i) {
    i *= 10;
    r++;
  }

  return r;
}


int main(){

  unsigned int n;

  int n = 1;
  while (n) {

  printf("Que número?\n");

  scanf("%u", &n);
  printf("%d\n\n", qDig(n));

  }

}
