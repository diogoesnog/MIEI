/**
@file bestscores.h
@brief Um header com as funções necessárias para leitura e escrita em ficheiro de texto dos bestscores.
*/

#include <stdio.h>

/** \brief Array de inteiros com capacidade para 5 scores. */
int scores[5];
/** \brief Array de inteiros com capacidade para 5 scores mas inicializado a 0. */
int vazio[5] = {0,0,0,0,0};

/**
\brief Função que lê todos os scores dum ficheiro de texto.
@returns Scores.
*/
int* ler_scores() {   
    FILE * fp;
    fp=fopen("/var/www/html/files/scores.txt","r");
    if (fp == NULL) return vazio;
        if(fscanf(fp, "%d\n%d\n%d\n%d\n%d\n", &scores[0],&scores[1],&scores[2],&scores[3],&scores[4])){}; // colocado num if para eliminar o warning do fscanf
    fclose(fp);
    return scores; 
}

/**
\brief Função que escreve o score num ficheiro de texto de forma ordenada.
@param e Score recebido para ser escrito.
*/
void escreve_score(int score) {
    int i, temp, j;
    FILE * fp;
    int* scores2 = ler_scores();
    fp=fopen("/var/www/html/files/scores.txt","w");
    
    if (score>scores2[4]) scores2[4] = score;
    for (i = 0; i < 5; i++)
    {
        for (j = i + 1; j < 5; j++)
        {
            if (scores2[i] < scores2[j])
            {
                temp = scores2[i];
                scores2[i] = scores2[j];
                scores2[j] = temp;
            }
        }
    }
    for (i = 0; i<5; i++) fprintf(fp,"%d\n",scores2[i]);
    fclose(fp);
}