#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <libxml/parser.h>
#include <date.h>
#include <tree.h>

typedef struct PostsAtr {
  xmlChar* id;
  xmlChar* postTypeId; 
  xmlChar* parentId;
  xmlChar* creationDate;
  int ndataigual;
  int nrespostas;
  xmlChar* score;
  xmlChar* commentCount;
  xmlChar* ownerUserId;
  xmlChar* title;
  xmlChar* tag;
  GSList* datalistperg;
  GSList* datalistres;
  GSList* scorelist;
  GSList* nresplist;
  GSList* userPostlist;
  GTree* postTreeResp;
  GSList* respostalist;
} *PostsAtr;


PostsAtr inicializaPostsAtr();
GHashTable* inicializaPostHashtable();
void HashForEachResMostResClean(GHashTable* hashposts, Info info);
void freePostsAtr(PostsAtr p);
void adicionaPostTreeRes(GHashTable* hashposts, PostsAtr pres);

void encontraMelhorRespostaTree(GTree* tree, Info info);