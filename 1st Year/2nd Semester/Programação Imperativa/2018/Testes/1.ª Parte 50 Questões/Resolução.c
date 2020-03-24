/** 
 * @author (Diogo Nogueira)
 * @version (03.2018)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Questão 1
int main () {

	int i;
	int j = 0;

	while (i != 0) {
	 	scanf ("%i", &i);
	 	if (i>j) {
	 		j=i;
	 	}
	}

	 printf ("O maior elemento da sequência é: %i\n", j);

	 return 0;

}

// Questão 2
int main () {

	int i, media;
	int soma  = 0;
	int nr = 0;

	while (i != 0) {
		scanf ("%i", &i);8
		soma += i;
		nr++;
	}

	media = soma/nr;
	printf ("A média da sequência é: %i\n", media);

	return 0;
}

// Questão 3
int main () {
	int n;

	int numero1 = INT_MIN;
	int numero2 = INT_MIN; 

	while ( n != 0 ) {
	
	scanf("%d", &n);
	 	
		if( n > numero1 ) {
	 		numero2 = numero1;
			numero1 = n;
     	}
    	else {
			if( n > numero2 ) numero2 = n;
			}
	};

    printf ("O segundo maior número da sequência é: %d\n", numero2);
    return 0;
}

// Questão 4
int bitsUm (unsigned int x) {
	int numeroBits = 0;

	while (x > 0) {
		if (x%2 !=0) numeroBits++;
		x = x / 2;
	};

	return numeroBits;
}


// Questão 5
int trailingZ (unsigned int n) { //10 em 10
	int zeros = 0;

	while (n >= 0 && n%2 == 0) {
		zeros++;
		n=n/2;
	}
	return zeros;
}

// Questão 6
int qDig (unsigned int n) {
	int numeroDigitos = 0;

	while (n > 0) {
		numeroDigitos = numeroDigitos + 1;
		n = n / 10;
	};

	return numeroDigitos;
};
	
// Questão 7
char *strcat2 (char s1[], char s2[]) { 
 
	int i = strlen(s1);
	int j;

	for (j = 0; s2[j] != '\0'; j++) {
		s1[i] = s2[j];
		i++;
	}
	s1[i]='\0';

	return s1;
}

// Questão 8
char *strcpy (char s1[], const char s2[]) {
	int i;

	for (i = 0; s2[i] != '\0'; ++i) {
		s1[i] = s2[i];
	};

	s1[i] = '\0';

	return s1;
}

// Questão 9
int strcmp (char s1[], char s2[]) {
	int i = 0;
	
	while ( (s1[i] != '\0') || (s2[i] != '\0') )
	{
		if (s1[i] > s2[i]) return 1;
		if (s1[i] < s2[i]) return -1;
		if (s1[i] == s2[i]) i++;
	};
	
	return 0;
}

// Questão 10
char *strstr (char s1[], char s2[]) {
}

// Questão 11
void strrev (char s[]) {

	int i;
	char troca;
	int tamanho = mystrlen(s) - 1;

	for (i=0; i < tamanho; i++) {
		troca = s[i];
		s[i] = s[tamanho];
		s[tamanho] = troca;
		tamanho--;
	}
}

// Questão 12
void strnoV (char s[]){

    int i;
    int c = 0;

  for (i = 0; s[i] != '\0'; i++) {
    
        if(s[i] != 'a' && s[i] != 'e' && s[i] != 'i' && s[i] != 'o' && s[i] != 'u' &&
           s[i] != 'A' && s[i] != 'E' && s[i] != 'I' && s[i] != 'O' && s[i] != 'U') {
          
           s[c] = s[i];
           c++;
        }
    }
    
    s[c] = '\0';

}

// Questão 13
void truncW (char t[], int n) { 
	int i = 0;
	int j = 0;
	int contador = n;

	while (t[i] != '\0') {

		if (t[i] != ' ' && contador != 0) {
			t[j] = t[i];
			j++;
			i++;
			contador--;
		};

		if (t[i] != ' ' && contador == 0) {i++;};

		if(t[i] == ' ') {
			t[j] = t[i];
			j++; 
			i++; 
			contador = n;
		};		
}
	t[j]='\0';
}

// Questão 14
int conta (char c, char s[]) {

  int i;
  int resultado = 0;

  for (i = 0; s[i] != '\0'; i++) {
    if (s[i] == c) resultado++;
  }

  return resultado;
}

char charMaisfreq (char s[]) {

	char resultado;

	int i;
	int nrvezes;
	int maior = 0;

	for (i = 0; s[i] != '\0'; i++) {

		nrvezes = conta(s[i], s);

		if (nrvezes > maior) {
			maior = nrvezes;
			resultado = s[i];
		}
	}

	return resultado;
}

// Questão 15
int iguaisConsecutivos (char s[]) {

	int i;
	int resultado = 0;
	int nriguais = 1;

	for (i = 0; s[i] != '\0'; i++)  {

		if (s[i] == s[i+1]) nriguais++;
		if (s[i] != s[i+1]) nriguais = 1;
		if (nriguais > resultado) resultado = nriguais;
	}

	return resultado;

}

// Questão 16


// Questão 17
int maiorPrefixo (char s1[], char s2[]) {

	int i = 0;
	int contador = 0;

	while ( (s1[i] != '\0') && (s2[i] != '\0') && (s1[i] == s2[i]) ) {
		i++;
		contador++;
	}

	return contador;
}

// Questão 18
int maiorSufixo (char st1[], char st2[]) {

	int i = strlen (s1) - 1; // Penúltimo índice do Array s1.
	int j = strlen (s2) - 1; // Penúltimo índice do Array s2.
	int contador = 0;
	
	while (s1[i] == s2[j]) {
		i--;
		j--;
		contador++;
	}

	return contador;
}

// Questão 19


// Questão 20
int contaPal (char s[]) {

	int resultado = 0;
	int flag = 0;
	int i = 0;

	while (s[i] != '\0') {

		flag = 0;

		while ( (s[i] != '\0') && (s[i] != ' ' ) ) {
			i++;
			flag = 1;
		}

		while ( (s[i] != '\0') && (s[i] == ' ') ) i++;

		if (flag == 1) resultado++; 
	}

	return resultado;
}

// Questão 21
int contaVogais (char s[]) {
	int i;
	int resultado = 0;

	for (i=0; s[i]!='\0'; i++) {
		if (s[i]=='A' || s[i]=='a' || s[i]=='E' || s[i]=='e' 
			|| s[i]=='I' || s[i]=='i' || s[i]=='O' || s[i]=='o' 
			|| s[i]=='U' || s[i]=='u') resultado++;
	}

	return resultado;
}

// Questão 22
int contidaAux (char c, char d[]) {

	int i;
	int resultado = 0;

	for (i = 0; d[i] != '\0'; i++) {

		if (c == d[i]) {resultado = 1; break;}
		else resultado = 0;

	}

	return resultado;
}

int contida (char a[], char b[]) {

	int i;
	int resultado = 0;

	for (i = 0; a[i] != '\0'; i++) {
		if (contidaAux(a[i],b)) resultado++;
		else {resultado = 0; break;}
    }

    if (resultado > 0) return 1;
    else return 0;
}

// Questão 23
int palindroma (char s[]) {

	int i = 0;
	int tamanho = strlen(s) - 1;
	int resultado = 1;

	while ( (resultado == 1) && (i <= tamanho) ) {

		if (s[i] != s[tamanho]) resultado = 0;
		else {i++; tamanho--;}
	}

	return resultado;

}

// Questão 24
int remRep (char x[]) {

	int i = 0;
	int j = 0;

	while(x[j] != '\0') {

		x[i] = x[j];

		while( (x[j] != '\0') && (x[j] == x[i]) ) {j++;}
		
		i++;
	}

	x[i] = '\0';
	return i;
}

// Questão 25
int limpaEspacos (char t[]) {

	int i = 0;
	int j = 0;

	while (t[j] != '\0') {

		t[i] = t[j];

		if (t[j] == ' ') {

			while ( (t[j] != '\0') && (t[j] == ' ') ) {j++;}
		
			j--;
		}  
	
		i++;
		j++;
	}

	t[i] = t[j];
	return i;
}

// Questão 26
void insere (int s[], int N, int x){

    int i = 0;
    
    while (x > s[i]) i++;
    
    int j;
    
    for (j=N; j>i; j--) {
        s[j] = s[j-1];
    }
    
    s[i] =  x;
}


// Questão 27

// Questão 28
int crescente (int a[], int i, int j) {
       int resultado = 1;
       
       while( (resultado == 1) && (i < j) ) {
           
           if(a[i] <= a[i+1]) {
               resultado = 1; 
               i++;
            }
           
           else {resultado = 0; break;}
        }
        
    return resultado;
 }


// Questão 29
int retiraNeg (int v[], int N) {
      
    int naoRetirados = 0;
    int i;
      
    for (i=0; i<N; i++) {
          
        if (v[i] > 0) {v[naoRetirados] = v[i]; naoRetirados++;}
         
    }
      
     return naoRetirados;
}

// Questão 30
int menosFreqAux (int elemento, int a[], int tamanho) {   
    
    int i;                                     
    int resultado  = 0;

    for (i = 0; i < tamanho; i++) {
      if (a[i] == elemento) resultado++;
    }
    return resultado;
  }

int menosFreq(int v[], int N) {

    int i;
    int auxiliar;
    int resultado1 = INT_MAX; 
    int resultado2 = v[0];                   
                  
    for (i = 0; i < N; i++) {		     
   
    auxiliar = menosFreqAux(v[i], v, N);         

    	if (resultado1 > auxiliar) {
      		resultado1 = auxiliar;
      		resultado2 = v[i];
    	}
  	}
  
  return resultado2;
}

// Questão 31
int maisFreqAux (int elemento, int a[], int tamanho) {   
    
    int i;                                     
    int resultado  = 0;

    for (i = 0; i < tamanho; i++) {
      if (a[i] == elemento) resultado++;
    }
    return resultado;
  }

int maisFreq(int v[], int N) {

    int i;
    int auxiliar;
    int resultado1 = INT_MIN; 
    int resultado2 = v[0];                   
                  
    for (i = 0; i < N; i++) {		     
   
    auxiliar = maisFreqAux(v[i], v, N);         

    	if (auxiliar > resultado1) {
      		resultado1 = auxiliar;
      		resultado2 = v[i];
    	}
  	}
  
  return resultado2;
}

// Questão 32
int maxCrescAux (int a, int b[], int tamanho) {
    
    int i = a;
    int resultado = 1;
    
    while (b[i] <= b[i+1]) {
            i++;
            resultado++;
    }
    
    return resultado;
}

int maxCresc (int v[], int N) {
    
    int i;
    int auxiliar = 0;
    int resultado = 0;
    
    for (i=0; i<N; i++) {
        
        auxiliar = maxCrescAux(i, v, N);
        if (auxiliar > resultado) resultado = auxiliar;
    }

    return resultado;
}

// Questão 33

// Questão 34
int elimRepOrd (int v[], int N) {
    
    int i;
    int resultado = 1;
    
    for (i=1; i<N; i++) {
        
        if (v[i] != v[i-1]) {
            v[resultado] = v[i];
            resultado++;
        }
    }
    
    return resultado;
}

// Questão 35
int comunsOrd (int a[], int na, int b[], int nb){
       
       int i = 0;
       int j = 0;
       int resultado = 0;
       
       while (i<na && j<nb) {
           
           if (a[i] == b[j]) {
               i++;
               j++;
               resultado++;
           }
           if (a[i] < b[j]) i++;
           if (a[i] > b[j]) j++;
       }
       
       return resultado;
}

// Questão 36
int comunsAux (int elemento, int vetor[], int tamanho)  {
    
    int i;
    int resultado = 0;
    
    for (i=0; i<tamanho; i++) {
        if (vetor[i] == elemento) {resultado = 1; break;}
        else {resultado = 0;}
    }
    
    return resultado;
}


int comuns (int a[], int na, int b[], int nb){
      
      int resultado = 0;
      int i;
      
      for (i=0; i<na; i++) {
          
          if(comunsAux(a[i], b, nb)) resultado++;
      }
      
      return resultado;
}

// Questão 37
int minInd (int v[], int n) {
    
    int i;
    int elemento = v[0];
    int resultado = 0;
   
   for (i=0; i<n; i++) {
       
       if (v[i] < elemento) {
           resultado = i;
           elemento = v[i];
        }
   }
  
   return resultado;
}

// Questão 38
void somasAc (int v[], int Ac [], int N){
  
  int i;
  int soma = 0;
  
  for (i=0; i<N; i++) {
      soma = soma + v[i];
      Ac[i] = soma;
  }
}

// Questão 39
int triSup (int N, float m [N][N]){

	int i;
	int j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < i; j++) {
      if (m[i][j] != 0) return 0;
    }
  }
  return 1;
}

// Questão 40
void transposta (int N, float m[N][N]) {

    int i, j; 
    float guarda;
  
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N; j++) {
      
            guarda = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = guarda;
        }
    }
}

// Questão 41
void addTo (int N, int M, int a [N][M], int b[N][M]){

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      a[i][j] += b[i][j];
    }
  }
}

// Questão 42
int unionSet (int N, int v1[N], int v2[N], int r[N]) {

	int i;

  	for(i = 0; i < N; i++){
    	if (v1[i] == 1 || v2[i] == 1) r[i] = 1;
    	else r[i] = 0;
  	}

  return 0;
}

// Questão 43
int intersectSet (int N, int v1[N], int v2[N], int r[N]) {

	int i;

  	for(i = 0; i < N; i++){
    	r[i] = v1[i] && v2[i];
  	}

  return 0;
}

// Questão 45
int unionMSet (int N, int v1[N], int v2[N], int r[N]){

	int i;

  	for(i = 0; i < N; i++){
    r[i] = (v1[i] + v2[i]);
  	}

  return 0;
}

// Questão 46
int cardinalMSet (int N, int v[N]) {
  
  int soma = 0;
  int i;

  for(i = 0; i < N; i++){
    soma +=v[i];
  }

  return soma;
}

// Questão 47
typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;

typedef struct posicao {
  int x, y;
} Posicao;

Posicao posFinal (Posicao inicial, Movimento mov[], int N) {

    int i;
    
	for (i=0; i<N; i++) {

		if (mov[i] == Norte) inicial.y++;
		if (mov[i] == Sul) inicial.y--;
		if (mov[i] == Este) inicial.x++;
		if (mov[i] == Oeste) inicial.x--;

	}
	
	return inicial;
}

// Questão 49
typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;

typedef struct posicao {
  int x, y;
} Posicao;

int maisCentral (Posicao pos[], int N) {

	int i;
	int indice = 0;
	int distancia =  abs(pos[0].x) + abs(pos[0].y);
	int teste;

	for (i=0; i<N; i++) {

		teste = abs(pos[i].x) + abs(pos[i].y);

		if (teste < distancia) {
			distancia = teste;
			indice = i;
		}
	}
	return indice;
}

// Questão 50
typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;

typedef struct posicao {
  int x, y;
} Posicao;


int vizinhos (Posicao p, Posicao pos[], int N){
  
  int conta = 0;

  for(int i = 0; i < N; i++){

    if (abs(p.x - pos[i].x) + abs(p.y - pos[i].y) == 1){
      conta++;
    }
  }

  return conta;
}
