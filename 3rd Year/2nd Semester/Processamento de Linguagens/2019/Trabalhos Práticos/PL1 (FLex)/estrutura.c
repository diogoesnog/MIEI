#include "estrutura.h"

struct noticia {
    List tags;
    char *id;
    char *categoria;
	char *titulo;
	char *autorData;
    char *texto;
	struct noticia *proxima;
}; 

// Funções necessárias para processamento da Estrutura das Notícias

int hashCode(char *key){
    int i,k=0;
    for(i=0;key[i]!='\0';i++){
        k += key[i];
    }
    return (k%HSIZE);
}

Noticia* inicializaNoticia(){
	Noticia *noticia = (Noticia*) malloc(sizeof(Noticia));
 
    noticia->tags = NULL; 
	noticia->id = EMPTY;
	noticia->categoria = EMPTY;
	noticia->titulo = EMPTY;
	noticia->autorData = EMPTY;
    noticia->texto = EMPTY;
	noticia->proxima = NULL;

	return noticia;
}

void inicializaNoticias(HashNoticias noticias){
	
	int i;

	for (i=0; i<HSIZE; i++){
		Noticia *noticia = (Noticia*) malloc(sizeof(Noticia));

        noticia->tags = NULL; 
		noticia->id = EMPTY;
		noticia->categoria = EMPTY;
		noticia->titulo = EMPTY;
		noticia->autorData = EMPTY;
        noticia->texto = EMPTY;
		noticia->proxima = NULL;

		noticias[i] = noticia;
	}
}

void libertaNoticias(HashNoticias noticias){
	
	int i;

	Noticia *atual;
	Noticia *proxima;

	for (i=0; i<HSIZE; i++){

		proxima = noticias[i]->proxima;
		atual = noticias[i];

		while (proxima != NULL){
			free(atual);
			atual = proxima; 
			proxima = proxima->proxima;
		}

		free(proxima);
	}
}

// Funções de inserção na Estrutura das Notícias

void insereNoticia(HashNoticias noticias, Noticia *noticia){
	
	int chave = hashCode(noticia->id);

	if (strcmp(noticias[chave]->id,EMPTY)==0){
		noticias[chave] = noticia;
	}
	else {
		noticia->proxima = noticias[chave]->proxima;
		noticias[chave]->proxima = noticia;
	}

}

void insereTags(Noticia *noticia, char *tag){
	noticia->tags = insereTag(noticia->tags,tag);
}

// Funções que definem os parâmetros da Notícia

void setId(Noticia *noticia, char *id){
	noticia->id = id;
}

void setCategoria(Noticia *noticia, char *categoria){
	noticia->categoria = categoria;
}

void setTitulo(Noticia *noticia, char *titulo){
	noticia->titulo = titulo;
}

void setAutorData(Noticia *noticia, char *autorData){
	noticia->autorData = autorData;
}

void setTexto(Noticia *noticia, char *texto){
	noticia->texto = texto;
}

// Funcões Úteis (algumas para teste)

void printNoticia(Noticia *noticia){
	
	displayListTags(noticia->tags);
	printf("Id: %s\n",noticia->id);
	printf("Categoria: %s\n",noticia->categoria);
	printf("Title: %s\n",noticia->titulo);
	printf("Autor/Data: %s\n",noticia->autorData);
	printf("Texto: %s\n",noticia->texto);
}

void displayHashP(HashNoticias hp){
	int i;

	for (i=0;i<HSIZE;i++){
		if (hp[i]!=NULL){;
			printf("hp[%d] - Id post = %s , Titulo = %s , Autor = %s, Categoria = %s, Texto = %s\n",i,hp[i]->id,hp[i]->titulo,hp[i]->autorData, hp[i]->categoria,hp[i]->texto);  
                Noticia * ptr = hp[i]->proxima;
				while(ptr != NULL) {
					printf("----> Id post = %s , Titulo = %s , Autor = %s, Categoria = %s, Texto = %s\n",ptr->id,ptr->titulo,ptr->autorData, ptr->categoria,ptr->texto);
					ptr = ptr->proxima;
				}	
		}
		else fprintf(stderr, "Pointer é null\n");
	}
} 
List procuraTags(HashNoticias noticias, char *id){

	int chave = hashCode(id);

	if(strcmp(noticias[chave]->id,id)==0){
		return noticias[chave]->tags;
	}

	return NULL;
}

// Funções para fazer o Parse e gerar os ficheiros HTML

void parsingFich(Noticia *noticia, int *tamanho){
	
	printf("Tamanho: %d\n", *tamanho);
	char *filename = (char*)malloc(sizeof(char)*(*tamanho));
	strcpy(filename,noticia->id);
	strcat(filename,".html");
	printf("Id Notícia: %s\n",noticia->id);
	
	FILE * file = fopen(filename,"w");
	
	// Começar o ficheiro HTML

	fprintf(file,"<html>\n<head>\n<meta charset='UTF-8'/>\n");
	fprintf(file,"<title>%s</title></head>\n",noticia->titulo);
	fprintf(file,"<pub id=%s>\n",noticia->id);
	fprintf(file,"<body>\n");
	fprintf(file,"<h1>%s</h1>\n",noticia->titulo);
	fprintf(file,"<author_date><p>%s\n</p></author_date>\n",noticia->autorData);
	fprintf(file,"<category><p>%s</p></category>\n",noticia->categoria);
	fprintf(file,"<p><tags>\n");
	parseTags(noticia->tags,file,filename);
	fprintf(file,"\n</tags></p>\n");
	fprintf(file,"<text>\n%s</text>\n",noticia->texto);
	fprintf(file,"</pub>\n</body>\n</html>");
	fclose(file);
	free(filename);

	printf("Ficheiro HTML criado.\n");
}

void parseTotal(HashNoticias noticias){

	int i;

	int *total =(int *)malloc(sizeof(int));
	int sizeF = 0;
	int sizeH = strlen(".html");
	Noticia * aux;

	for(i=0; i<HSIZE; i++){

		if(strcmp(noticias[i]->id,EMPTY)){
			sizeF = strlen(noticias[i]->id);
			*total = (sizeF+sizeH+1);
			parsingFich(noticias[i],total);
		}
		aux = noticias[i]->proxima;
		while(aux){
			sizeF = strlen(aux->id);
			*total = sizeF+sizeH;
			parsingFich(aux,total);
			aux = aux->proxima;
		} 
	}
	printf("Fim.\n");

	free(total);
}

void parseHashToFic(HashNoticias noticias){

	FILE *f = fopen("hash.txt","w");

	int i;
	Noticia * auxiliar;

	for(i=0; i<HSIZE; i++){
		fprintf(f,"\n--------------------\n");
		fprintf(f,"h[%d]\n",i);
		fprintf(f,"Tags: \n");
		fichTags(noticias[i]->tags,f);
		fprintf(f,"Id Notícia: %s\n",noticias[i]->id);
		fprintf(f,"Categoria: %s\n",noticias[i]->categoria);
		fprintf(f,"Título: %s\n",noticias[i]->titulo);
		fprintf(f,"Autor/Data: %s\n",noticias[i]->autorData);
		auxiliar = noticias[i]->proxima;

		while(auxiliar){
			fprintf(f,"\n--------------------\n");
			fprintf(f,"Tags: \n");
			fichTags(auxiliar->tags,f);
			fprintf(f,"Id Notícia: %s\n",auxiliar->id);
			fprintf(f,"Categoria: %s\n",auxiliar->categoria);
			fprintf(f,"Título: %s\n",auxiliar->titulo);
			fprintf(f,"Autor/Data: %s\n",auxiliar->autorData);

			auxiliar = auxiliar->proxima;
		}
	}
	
	fclose(f);
}