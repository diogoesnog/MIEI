#include <stdio.h>

#include "read.h"

int limpaBuffer() {

  char c;

  do{
	c=getchar();
  } while(c!='\n');

  return 0;

}

int isDigit( char d ) {
  return ((d>='0')&&(d<='9'))? 1:0;
}

int parseInt() {

  char c;
  int valor=0;

  c = getchar();

  while(isDigit(c)) {
	valor = valor*10 + c-'0';
	c=getchar();
  }

  if(c=='\n') return valor;
  else {
	limpaBuffer();
	return INPUTERROR;
  }
}

int readInt() {

	int n;

	do {
	  printf("?? ");
	  n = parseInt();
	} while(n == INPUTERROR);


	return n;
}
