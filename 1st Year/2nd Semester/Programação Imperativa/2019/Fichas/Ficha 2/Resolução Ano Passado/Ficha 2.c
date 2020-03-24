#include <stdio.h>

// Resolução da Ficha nº.2

// (1)
float multInt1 (int n, float m) {
    int r = 0;
    while (n>0) {
        r = r + m;
        n--;
    }
    printf("%d", r);
}

// (2)
float multInt2 (int n, float m) {
    
    int r = 0;

    while (n>=1)  {
       
        if (n%2 == 0) r = r + 0; 
        else r = r+m;
        
        n = n/2;
        m = m*2;
    }

    printf("%d", r);
}

// (3)
int mdc (int a, int b) {
    
}