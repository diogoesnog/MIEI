#include "tags.h"

#define EMPTY ""
#define HSIZE 10000

typedef struct noticia Noticia, *HashNoticias[HSIZE];

int hashCode(char *key);
Noticia* inicializaNoticia();
void inicializaNoticias(HashNoticias noticias);
void libertaNoticias(HashNoticias noticias);

void insereNoticia(HashNoticias noticias, Noticia *noticia);
void insereTags(Noticia *noticia, char *tag);

void setId(Noticia *noticia, char *id);
void setCategoria(Noticia *noticia, char *categoria);
void setTitulo(Noticia *noticia, char *titulo);
void setAutorData(Noticia *noticia, char *autorData);
void setTexto(Noticia *noticia, char *texto);

void printNoticia(Noticia *noticia);
void displayHashP(HashNoticias noticias);
List procuraTags(HashNoticias noticias, char *id);

void parsingFich(Noticia *noticia, int *tamanho);
void parseTotal(HashNoticias noticias);
void parseHashToFic(HashNoticias noticias);