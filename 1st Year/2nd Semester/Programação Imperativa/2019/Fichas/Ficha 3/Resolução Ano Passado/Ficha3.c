#include <stdio.h>

// Resolução da Ficha nº.3

// (1)
// (a)
int x [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

int *y, *z, i; 
y = x; z = x+3; 
for (i=0; (i<5); i++) { 
	printf ("%d %d %d\n", x[i], *y, *z); 
	y = y+1; z = z+2; 
}

/* Este excerto inicia o x a 3 e o y a 4. Após isso, o x passa a ser 12 (3*4) e o y passa a ser 16 (12+4).
Por fim, imprime estes resultados. */
