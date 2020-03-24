/** 
 * @author (Diogo Nogueira)
 * @version (19.02.2019)
 */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

// Questão 1

int readMaiorElemento(){

    int numero;
    int maior = 0;

    printf("Introduz a sua sequência de números (terminada em 0).\n");

    while(numero != 0){
        scanf("%i",&numero);
        if(numero>maior) maior = numero;
    }

    return maior;
}

// Questão 2

int readMedia(){

    int numero;

    int soma = 0;
    int quantidade = 0;
    int media;

    printf("Introduz a sua sequência de números (terminada em 0).\n");
    
    while(numero != 0){
        scanf("%i",&numero);
        soma += numero;
        quantidade++;
    }

    media = soma/(quantidade-1);
    return media;
}

// Questão 3

int segundoMaiorElemento(){
  
  int maior;
  int segundo=0;
  int prox=0;


  printf("Introduz aqui uma sequência de números terminada em 0: ");
  scanf("%d\n",&prox);
  maior=prox;
  while(prox!=0){
    scanf("%d",&prox);
    if(prox>maior){
    segundo=maior;
    maior=prox; 
    }
  }

  return segundo;
}

// Questão 7

char *concatenaString (char s1[], char s2[]) { 

    int tamanhoString1 = strlen(s1);

    for(int j=0; s2[j] != '\0'; j++){
        s1[tamanhoString1] = s2[j];
        tamanhoString1++;
    }

    s1[tamanhoString1] = '\0';

    return s1;
}

// Questão 8

char *copiaString (char *dest, char source[]) {

    int i;

    for(i=0; source[i] != '\0'; i++){
        dest[i] = source[i];
    }

    dest[i] = '\0';

    return dest;
}

// Questão 9

int comparaStrings (char s1[], char s2[]) {

    int i = 0;

    while((s1[i] != '\0') || (s2[i] != '\0')){
        if(s1[i] > s2[i]) return 1;
        if(s1[i] < s2[i]) return -1;
        if(s1[i] == s2[i]) i++
    }

    return 0;
}

// Questão 10
//  Posição onde a String s2 ocorre na String s1.

char *posicaoString (char s1[], char s2[]) {

}

// Questão 11

void inverteString (char s[]) {

    char caraterTroca;
    int tamanhoString = strlen(s)-1;

    for(int i=0; i<tamanho; i++){
        caraterTroca = s[i];
        s[i] = s[tamanhoString];
        s[tamanhoString] = troca;
        tamanhoString--;
    }
}

// Questão 12

void retiraVogais (char s[]){

    int indice = 0;

    for(int i=0; s[i]!='\0'; i++){
        if(s[i] != 'a' && s[i] != 'e' && s[i] != 'i' && s[i] != 'o' && s[i] != 'u' &&
           s[i] != 'A' && s[i] != 'E' && s[i] != 'I' && s[i] != 'O' && s[i] != 'U') {
          
           s[indice] = s[i];
           c++;
        }
    }

    s[indice] = '\0';
}

// Questão 13

void truncaPalavras(char texto[], int maximoLetras){

    int i;
    int indiceNovo;
    int contador = maximoLetras;

    while(texto[i] != '\0'){

        if(texto[i] != ' ' && contador != 0){
            texto[indiceNovo] = texto[i];
            indice++;
            indiceNovo++;
            contador--;
        }

        if(texto[i] != ' ' && contador ==0) i++;

        if(texto[i] == ' '){
            texto[indiceNovo] = texto[i];
            indice++;
            indiceNovo++;
            contador = maximoLetras;
        }
    }

    texto[indiceNovo] = "\0";
}

// Questão 14

int conta(char caracter, char caracteres[]){

    int resultado;
    int i;

    for(i=0; caracteres[i] != '\0'; i++){
        if(caracteres[i]==caracter) resultado++;
    }

    return resultado;
}

char charMaisfreq(char s[]){

    char maisFrequente;
    int i;

    int quantidade;
    int maior = 0;

    for(i=0; s[i] != '\0'; i++){
        quantidade = conta(s[i], s);

        if(quantidade>maior){
            maior = quantidade;
            maisFrequente = s[i];
        }
    }

    return maisFrequente;
}

// Questão 15

int iguaisConsecutivos(char s[]){

    int resultado = 0;
    int numeroIguais = 1;

    for(int i=0; s[i] != '\0'; i++){

        if(s[i] == s[i+1]) numeroIguais++;
        if(s[i] != s[i+1]) numeroIguais = 1;
        if(numeroIguais>resultado) resultado = numeroIguais;
    }

    return resultado;
}

// Questão 16

int diferentesConsecutivos(char s[]){

    int resultado = 0;
    int numeroDiferentes = 1;

    for(int i=0; s[i] != '\0'; i++){

        if(s[i] == s[i+1]) numeroDiferentes = 1;
        if(s[i] != s[i+1]) numeroDiferentes++;
        if(numeroDiferentes>resultado) resultado = numeroDiferentes;
    }

    return resultado;
}

// Questão 17

int maiorPrefixo (char s1 [], char s2 []){

    int comprimento = 0;
    int i = 0;
    
    while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]){
        comprimento++;
        i++;
    }

    return comprimento;
}

// Questão 18

int maiorSufixo (char st1[], char st2[]){

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

int conta (char s1[], char s2[], int indice){
    
    int j = 0;
    int i = indice;
    int resultado = 0;
    
    while(s1[indice]!='\0'){

        if(s1[indice] == s2[j]){
            resultado++;
            indice++;
            j++;
        }
        else return 0;
    }

    return resultado;
}

int sufPref (char s1[], char s2[]) {

    int tamanhoSufixo = 0;
    int resultado = 0;
    int i = 0;

    while(s1[i] != '\0'){
        
        resultado = conta(s1, s2, i);
        
        if(resultado>tamanhoSufixo) tamanhoSufixo = resultado;
        
        i++;
    }
    
    return tamanhoSufixo;
}

// Questão 20

int contaPal (char s[]) {
    
    int palavra = 0;
    int numeroPalavras = 0;
    int i = 0;
    
    while(s[i] != '\0'){
       
       if(s[i] == ' ' || s[i] == '\n') palavra = 0;
       
       else if(palavra == 0) {palavra = 1; numeroPalavras++;}
       
       i++;
    }
    
    return numeroPalavras;
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

int existe(char a, char b[]) {
    
    int i;
    int resultado = 0;
    
    for(i=0; b[i]!='\0'; i++){
        if(a==b[i]) resultado=1;
    }
    
    return resultado;
}


int contida (char a[], char b[]) {
    
    int i;
    int resultado = 0;
    
    for(i=0; a[i]!='\0'; i++){
        if(existe(a[i],b)==1) resultado++;
        else{resultado=0; break;}
    }
    
    if(resultado>0) resultado = 1;
    
    return resultado;
}

// Questão 23


int palindroma (char s[]) {

    int tamanho = strlen(s)-1;
    int i =0;
    int resultado = 1;
    
    while(i<tamanho){
        if(s[i] == s[tamanho]) {
            tamanho--; i++;
        }
        else return 0;
    }

    return resultado;
}

// Questão 24

int remRep (char texto[]) {

    int i = 0;
    int j = 0;
    
    while(texto[i]!='\0'){
        
        texto[j]=texto[i];
        
        while(texto[i]==texto[j]) i++;
        
        j++;
    }
    
    texto[j]='\0';
    
    return j;
}

// Questão 25

int limpaEspacos (char texto[]) {
    
    int novoIndice = 0;
    int indice = 0;
    
    while(texto[indice] != '\0'){
       
       texto[novoIndice] = texto[indice];
       
       if(texto[novoIndice] == ' '){
           while(texto[indice] == ' ') indice++;
       }
       else indice++;
       
       novoIndice++;
    }
    
    texto[novoIndice] = '\0';
    
    return novoIndice;
}

// Questão 26

void insere (int s[], int N, int x){

    int i=0;
    int j;
    
    while(x>s[i]) i++;
    
    for(j=N; j>i; j--){
        s[j] = s[j-1];
    }
    
    s[i] = x;
}

// Questão 27

// Questão 28

int crescente (int a[], int i, int j){

    int resultado=1;

    while(resultado==1 && i<j){
        if(a[i]<=a[i+1]) {
            resultado=1;
            i++;
        }
        else resultado=0;
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

int ocorrencias (int vetor[], int elemento, int tamanho){
    
    int i=0;
    int resultado=0;
    
    while(i<tamanho){
        if(vetor[i]==elemento) resultado++;
        i++;
    }
    
    return resultado;
}


int menosFreq (int v[], int N){

    int i=0;
    int auxiliar;
    int menosFrequente=INT_MAX ;
    int resultado=v[0];
    
    while(i<N){
        
        auxiliar=ocorrencias(v,v[i],N);
        
        if(menosFrequente>auxiliar){
            menosFrequente=auxiliar;
            resultado=v[i];
        }
        
        i++;
    }
    
    return resultado;
}

// Questã0 31

int ocorrencias (int vetor[], int elemento, int tamanho){
    
    int i=0;
    int resultado=0;
    
    while(i<tamanho){
        if(vetor[i]==elemento) resultado++;
        i++;
    }
    
    return resultado;
}

int maisFreq (int v[], int N){

    int i=0;
    int auxiliar;
    int maisFrequente=0;
    int resultado = v[0];
    
    while(i<N){
        auxiliar = ocorrencias(v,v[i],N);
        
        if (auxiliar>maisFrequente){
            maisFrequente=auxiliar;
            resultado = v[i];
        }
        
        i++;
    }
    
    return resultado;
}

// Questão 32

int maiorCrescente (int v[], int indice, int tamanho) {
    
    int i=indice;
    int resultado=1;
    
    while(v[i]<=v[i+1]){
        i++;
        resultado++;
    }
    
    return resultado;
}


int maxCresc (int v[], int N) {

    int i;
    int auxiliar;
    int tamanhoSequencia=0;
    
    for(i=0; i<N; i++){
        auxiliar=maiorCrescente(v,i,N);
        if(auxiliar>tamanhoSequencia) tamanhoSequencia=auxiliar;
    }
    
    return tamanhoSequencia;
}

// Questã0 33

int temElemento(int v[], int elemento, int indiceLimite) {
    
    int i;
    int resultado=0;
    
    for(i=0; i<indiceLimite; i++){
        if(v[i]==elemento) resultado=1;
    }
    
    return resultado;
}


int elimRepOrd (int v[], int N) {

    int i;
    int j=1;
    
    for(i=1; i<N; i++){
        
        if(temElemento(v,v[i],i)==0){
            v[j]=v[i];
            j++;
        }
    }
    
    return j;
}

// Questão 34

int elimRepOrd (int v[], int N) {
    
    int i;
    int resultado=1;
    
    for(i=1; i<N; i++){
        
        if(v[i]!=v[i-1]){
            v[resultado]=v[i];
            resultado++;
        }
    }
    
    return resultado;
}

// Questã0 35

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

// Questã0 36

int comunsAux (int elemento, int vetor[], int tamanho)  {
    
    int i;
    int resultado = 0;
    
    for (i=0; i<tamanho; i++) {
        if (vetor[i] == elemento) resultado=1;
    }
    
    return resultado;
}


int comunsOrd (int a[], int na, int b[], int nb){
      
      int resultado = 0;
      int i;
      
      for (i=0; i<na; i++) {
          
          if(comunsAux(a[i], b, nb)) resultado++;
      }
      
      return resultado;
}

// Questão 37

int minInd (int v[], int n) {
    
    int indiceMenorElemento=0;
    int menorElemento=v[0];
    int i;
    
    for(i=1; i<n; i++){
        if(v[i]<menorElemento){
            indiceMenorElemento=i;
            menorElemento=v[i];
        }
    }

    return indiceMenorElemento;
}

// Questão 38

void somasAc (int v[], int Ac [], int N){

    int i;
    int soma=0;
    
    for(i=0; i<N; i++){
        soma=soma+v[i];
        Ac[i]=soma;
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

void transposta (int N, float m [N][N]) {

    float guarda;
    int i;
    int j;
    
    for(i=0; i<N; i++){
        for(j=i+1; j<N; j++){
            guarda = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = guarda;
        }
    }
}


// Questão 41

// Questã0 46

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


// Questão 47

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


// Questão 48

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

// Função main para testar todas as questões

int main(int argc, char *argv[]){

    int maiorElemento = segundoMaiorElemento();
    printf("Maior Elemento: %i\n", maiorElemento);

}