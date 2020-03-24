#include "tags.h"

struct tags{
    char *tag;
    struct tags *proxima;
};

List insereTag(List tags, char *tag){

	List novaLista = (List) malloc(sizeof(struct tags));
	if (novaLista != NULL){
		novaLista->tag = tag;
		novaLista->proxima = tags;
	}

	return novaLista;
}

void displayListTags(List tags) {
	
	List listaTags = tags;

	while (listaTags!=NULL){
		printf ("Tag: %s\n",listaTags->tag);
		listaTags = listaTags->proxima;
	}
}

void parseTags(List l, FILE *f, char *name){

	FILE * tag;
	int sizeH = strlen(".html");
	int sizeF=0;
	int sizeT =0;
	char *filename;
	
	while(l){
		sizeF = strlen(l->tag);
		sizeT = sizeF+sizeH+1;
		filename = (char*)malloc(sizeof(char)*sizeT);
		strcpy(filename,l->tag);
		strcat(filename,".html");
		fprintf(f,"<tag>%s</tag>; ",l->tag);
		FILE *tagF = fopen(filename,"w");
		fprintf(tagF,"<li><a href='%s'>%s</a></li>\n",name,name);
		l = l->proxima;
		fclose(tagF);
		free(filename);
	}
}

void fichTags(List listaTags, FILE * f){
	
	int i=0;

	while(listaTags){
		fprintf(f,"Tag Número %d: %s", i++, listaTags->tag);
		listaTags = listaTags->proxima;
	}
}

void freeList(List tags){

	List auxiliar;

	while(tags){
		auxiliar = tags;
		tags = tags->proxima;
		free(auxiliar);
	}
}