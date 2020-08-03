#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <libxml/parser.h>
#include <hashTag.h>

#define VAZIO NULL


//funçao que incializa a Estrutura de tags que contem todos os parametros necessários as querys.
tagAtr inicializatagAtr(){
  tagAtr t = (tagAtr) malloc(sizeof (struct tagAtr));
  t->id = (xmlChar*)VAZIO;
  t->tagname = (xmlChar*)VAZIO; 
  t->samecountlist = NULL;
  t->nused = 1;
  t->tagsamecountlist = VAZIO;
  return t;
}
//funçao que liberta a memeoria de um tagAtr.
void freetagAtr(tagAtr t){
	g_slist_free(t->tagsamecountlist);
	free(t);
}
//funçao que inicializa a hashtable das tags.
GHashTable* inicializaTagHashtable(){
	return g_hash_table_new_full(g_str_hash, g_str_equal,free,freetagAtr);
}