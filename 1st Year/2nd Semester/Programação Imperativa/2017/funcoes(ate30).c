/** 
 * @author (Pirata)
 * @version (02.2016)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Questão 5:
 * Função que calcula o número de bits igual a 1 usados na representação
 * binária de um dado número n.
 */
int bitsUm (unsigned int n)
{
	int cont = 0;
	int rest;
	
	while(n != 0)
	{
		rest = n % 2;
		n = n / 2;
		cont = cont + rest;
	}
	return cont;
}

/**
 * Questão 6:
 * Função que calcula o número de bits a 0 no final da representação binária
 * de um número (i.e., o expoenta da maior potência de 2 que é divisor de
 * esse número).
 */
int trailingZ (unsigned int n)
{
	int count = 0;
	
	while(n > 0)
	{
		n = n / 2;
		if(n > 0)
			count++;
	}
	return count;
}

/**
 * Questão 7:
 * Função que calcula o número de dígitos necessários para escrever um
 * inteiro n em base decimal.
 */
int gDig (unsigned int n)
{
	int count = 0;
	
	while(n > 0)
	{
		n = n / 10;
		count++;
	}
	return count;
}

/**
 * Questão 8:
 * Função pré-definida em C, int strlen (char str[]), que calcula o
 * comprimento de uma String.
 */
int strlen_1 (char str[])
{
	int i;
	for(i = 0; str[i] != '\0'; i++);
	return i;
}

/* Deste modo está a trabalhar com endereços. */
int strlen_2 (char str[])
{
	char *s;
	for(s = str; *s; s++);
	return (s - str);
}

/**
 * Questão 9:
 * Função pré-definida em C, char *strcat (char s1[], char s2[]), que
 * concatena a string s2 a s1 (retornando o endereço da primeira).
 * 
 * NOTA: Assumindo que o s1 tem espaço suficiente para as duas strings.
 */
char *strcat_1 (char s1[], char s2[])
{
	int i = 0, j = 0;
	while(s1[i] != '\0')
		i++;
	while(s2[j] != '\0')
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return s1;
}

/* Usando a função strcpy. */
char *strcat_2 (char s1[], char s2[])
{
	strcpy(&s1[strlen(s1)], s2);
	return s1;
}

/**
 * Questão 10:
 * Função pré-definida em C, char *strcpy (char *dest, char source[]), que
 * copia a string source para a dest retornando o valor desta última.
 * 
 * NOTA: Assumindo que o dest tem espaço alocado suficiente.
 */
char *strcpy_1 (char *dest, char source[])
{
	char *sdest = dest;
	int i = 0;
	
	while(source[i] != '\0')
	{
		*sdest = source[i];
		sdest++; /* Passar apontador para a frente. */
		i++;
	}
	*sdest = '\0';
	return dest;
}

/**
 * Questão 11:
 * Função pré-definida em C, int strcmp (char s1[], char s2[]), que compara
 * (lexicograficamente) duas strings. Resultados:
 *  -> 0 se iguais.
 *  -> <0 se s1 < s2.
 *  -> >0 se s1 > s2.
 */
int strcmp_1 (char s1[], char s2[])
{
	int i = 0;
	while((s1[i] == s2[i]) && (s1[i] != '\0') && (s1[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

/**
 * Questão 12:
 * Função pré-definida em C, char *strstr (char s1[], char s2[]), que
 * determina a posição onde a string s2 ocorre em s1. A função deverá
 * retornar NULL caso s2 não ocorra em s1.
 */
char *strstr_1 (char s1[], char s2[])
{
	int i = 0;
	char *res = NULL;
	int len = strlen (s2);
	
	while((s1[i] != '\0') && (res == NULL))
	{
		if((s1[i] == s2[0]) && (strncmp (&s1[i], s2, len) == 0))
			res = &s1[i];
		i++;
	}
	return res;
}

/**
 * Questão 13:
 * Função que inverte uma string.
 */
void strrev (char s[])
{
	char help;
	int i = 0, end = strlen(s) - 1;
	
	while(i < end)
	{
		help = s[i];
		s[i] = s[end];
		s[end] = help;
		i++;
		end--;
	}
}

/**
 * Questão 14:
 * Função que retira todas as vogais de uma string.
 */
/* Função auxiliar apenas para verificar se um char é vogal ou não. */
int isVowel (char c)
{
	if((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') ||
		(c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U'))
		return 1;
	else
		return 0;
}

void strnoV (char s[])
{
	int i = 0, j = 0;
	while(s[j] != '\0')
	{
		while(isVowel (s[j]))
			j++;
		
		s[i] = s[j];
		if(s[i] != '\0')
		{
			i++;
			j++;
		}
	}
	s[i] = '\0';
}

/**
 * Questão 15:
 * Função que dado um texto t com várias palavras (as palavras estão
 * separadas em t por um ou mais espaços) e um inteiro n, trunca todas as
 * palavras de forma a terem no máximo n caracteres.
 */
void truncW (char t[], int n)
{
	int i, j = 0, x;
	for(i = 0; t[i] != '\0'; i++, j++)
	{
		for(x = n;(x > 0) && (t[i] != ' ') && (t[i] != '\0'); x--, i++, j++)
			t[j] = t[i];
		while((t[i] != '\0') && (t[i] != ' '))
			i++;
		t[j] = t[i];
	}
	t[j] = '\0';
}

/**
 * Questão 16:
 * Função que determina o carácter mais frequente de uma string. A função
 * deverá retornar 0 no caso da string ser vazia.
 */
char charMaisfreq (char s[])
{
	int i;
	int aux[256] = {0};
	char res = 0;
	
	for(i = 0; s[i] != '\0'; i++)
		aux[(int) s[i]] += 1;

	for(i = 0; i < 256; i++)
		if(aux[i] > aux[(int) res])
			res = i;
	
	return res;
}

/**
 * Questão 17:
 * Função que, dada uma string s calcula o comprimento da maior sub-string
 * com carácters iguais.
 */
int iguaisConsecutivos (char s[])
{
	int i;
	int max = 0, now = 0;
	
	for(i = 0; s[i] != '\0'; i++)
	{
		if(i == 0)
			now = 1;
		else
		{
			if(s[i] == s[i - 1])
				now++;
			else
			{
				if(max < now)
					max = now;
				now = 1;
			}
		}
	}
	/* preciso de fazer esta verificação de novo caso o mais longo seja no
	 * final da string. Faz menos verificações durante o ciclo mas sou
	 * obrigado a fazer uma última fora do ciclo. */
	if(max < now)
		max = now;
	
	return max;
}

/**
 * Questão 18:
 * Função que, dada uma string s calcula o comprimento da maior sub-string com
 * carácters diferentes.
 */
int difConsecutivos(char s[])
{
	int i;
	int max = 0, now = 0;
	
	for(i = 0; s[i] != '\0'; i++)
	{
		if(i == 0)
			now = 1;
		else
		{
			if(s[i] != s[i - 1])
				now++;
			else
			{
				if(max < now)
					max = now;
				now = 1;
			}
		}
	}
	/* preciso de fazer esta verificação de novo caso o mais longo seja no
	 * final da string. Faz menos verificações durante o ciclo mas sou
	 * obrigado a fazer uma última fora do ciclo. */
	if(max < now)
		max = now;
	
	return max;
}

/**
 * Questão 19:
 * Função que calcula o comprimento do maior prefixo comum entre as duas strings.
 */
int maiorPrefixo (char s1[], char s2[])
{
	int i = 0;
	while((s1[i] != '\0') && (s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	return i;
}

/**
 * Questão 20:
 * Função que calcula o comprimento do maior sufixo em comum entre as duas strings.
 */
int maiorSufixo (char st1[], char st2[])
{
	int i = strlen(st1) - 1, j = strlen(st2) - 1, res = 0;
	while((i >= 0) && (j >= 0) && (st1[i] == st2[j]))
	{
		i--;
		j--;
		res++;
	}
	return res;
}

/**
 * Questão 21:
 * Função que calcula o tamanho do maior sufixo de s1 que é um prefixo de s2.
 * Por exemplo, sufPref("batota","totalidade") deve dar 4 como resultado.
 */
int sufPref (char s1[], char s2[])
{
	int size = strlen(s1);
	int i = 0, j, aux1, res = 0, flag = 0;
	
	while((s1[i] != '\0') && (!flag))
	{
		res = 0;
		if(s1[i] == s2[0])
		{
			aux1 = i;
			j = 0;
			while((s1[aux1] != '\0') && (s2[j] != '\0') && (s1[aux1] == s2[j]))
			{
				aux1++;
				j++;
				res++;
			}
			if(res == (size - i))
				flag = 1;
		}
		i++;
	}
	return res;
}

/**
 * Questão 22:
 * Função que conta as palavras de uma string. Uma palavra é uma sequência
 * caracteres (diferente de espaço) terminada por um ou mais espaços.
 */
int contaPal (char s[])
{
	int res = 0, i = 0, flag;
	
	while(s[i] != '\0')
	{
		flag = 0;
		while((s[i] != '\0') && (s[i] == ' '))
			i++;
		while((s[i] != '\0') && (s[i] != ' '))
		{
			i++;
			flag = 1;
		}
		if(flag == 1)
			res++;
	}
	return res;
}

/**
 * Questão 23:
 * Função que retorna o número de vogais da string s. Considerando maiúsculas
 * e minúsculas.
 */
int contaVogais (char s[])
{
	int i, res = 0;
	for(i = 0; s[i] != '\0'; i++)
	{
		switch (s[i])
		{
			case 'a' :
			case 'e' :
			case 'i' :
			case 'o' :
			case 'u' :
			case 'A' :
			case 'E' :
			case 'I' :
			case 'O' :
			case 'U' : res++;
		}
	}
	return res;
}

/**
 * Questão 24:
 * Função que testa se todos os caracters da primeira string também aparecem
 * na segunda.
 */
int contida (char a[], char b[])
{
	int flag = 1, i = 0, j;
	while((a[i] != '\0') && (flag == 1))
	{
		j = 0;
		flag = 0;
		while((!flag) && (b[j] != '\0'))
		{
			if(b[j] == a[i])
				flag = 1;
			j++;
		}
		i++;
	}
	return flag; /* se lista vazia retorna Verdadeiro */
}

/**
 * Questão 25:
 * Função que testa se uma função é palíndrome, i.e., lê-se de igual forma
 * nos dois sentidos.
 */
int palindorome (char s[])
{
	int i = 0, f = strlen(s) - 1, flag = 1;
	while((flag) && (i <= f))
	{
		if(s[i] != s[f])
			flag = 0;
	}
	return flag;
}

/**
 * Questão 26:
 * Função que elimina de uma string todos os caracteres que se repetem sucessivamente
 * deixando lá apenas uma cópia. A função deverá retornar o comprimento da string
 * resultante.
 */
int remRep (char x[])
{
	int i = 0, j = 0;
	while(x[j] != '\0')
	{
		x[i] = x[j];
		while((x[j] != '\0') && (x[j] == x[i]))
			j++;
		i++;
	}
	x[i] = '\0';
	return i;
}

/**
 * Questão 27:
 * Função que elimina repetições sucessivas de espaços por um único espaço.
 * A função deve retornar o comprimento da string resultante.
 */
int limpaEspacos (char t[])
{
	int i = 0, j = 0;
	while(t[j] != '\0')
	{
		t[i] = t[j];
		if(t[j] == ' ')
		{
			while((t[j] != '\0') && (t[j] == ' '))
				j++;
			j--;
		}
		j++;
		i++;
	}
	t[i] = t[j];
	return i;
}

/**
 * Questão 28:
 * Função que insere um elemento (x) num vector ordenado. Assuma que as N
 * primeiras posições do vector estão ordenadas e que por isso, após a inserção
 * o vector terá as primeiras N+1 posições ordenadas.
 */
/* Como não diz que ordenação tem, fiz uma genérica com preferência para
 * CRESCENTE */
void insere (int v[], int N, int x)
{
	int i = 0;
	if(N > 0)
	{
		if(v[0] <= v[N-1])
		{
			while((i < N) && (v[i] < x))
				i++;
		}
		else
		{
			while((i < N) && (v[i] > x))
				i++;
		}
		while(N > i)
		{
			v[N] = v[N-1];
			N--;
		}
	}
	v[i] = x;
}

/**
 * Questão 29:
 * Função que dados vectores ordenados a (com na elementos) e b (com nb
 * elementos), preenche o vector r (com na+nb elementos) com os elementos
 * de a e b ordenados.
 */
void merge (int r[], int a[], int b[], int na, int nb)
{
	int i = 0, j;
	while(i < na)
	{
		r[i] = a[i];
		i++;
	}
	for(j = 0; j < nb; j++)
	{
		insere(r,i,b[j]);
		i++;
	}
}

/**
 * Questão 30:
 * Função que testa se os elementos do vector a, entre as posições i e j
 * (inclusivé) estão ordenados por ordem crescente. A função deve retornar
 * 1 ou 0 consoante o vector esteja ou não ordenado.
 */
int crescente (int a[], int i, int j)
{
	int res = 1;
	while((res == 1) && (i < j))
	{
		if(a[i] > a[i++])
			res = 0;
		i++;
	}
	return res;
}
