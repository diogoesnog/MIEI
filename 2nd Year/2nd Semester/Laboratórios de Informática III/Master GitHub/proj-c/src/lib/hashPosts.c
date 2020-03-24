#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <hashUser.h>

#define VAZIO NULL
// Função que inicializa a hashtable dos posts.
GHashTable* inicializaPostHashtable(){
    return g_hash_table_new_full(g_str_hash, g_str_equal,free,freePostsAtr);
}
// Função que aloca a estrutura de um post com os parametros necessários ás querys.
PostsAtr inicializaPostsAtr(){
  PostsAtr p = (PostsAtr) malloc(sizeof (struct PostsAtr));
  p->id = VAZIO;
  p->postTypeId = VAZIO; 
  p->commentCount = VAZIO;
  p->parentId = VAZIO;
  p->creationDate = VAZIO;
  p->score = VAZIO;
  p->ownerUserId = (xmlChar*)VAZIO;
  p->ndataigual = 1;
  p->title = (xmlChar*)VAZIO;
  p->nrespostas = 0;
  p->datalistperg = VAZIO;
  p->datalistres = VAZIO;
  p->scorelist = VAZIO;
  p->nresplist = VAZIO;
  p->userPostlist = VAZIO;
  p->respostalist = VAZIO;
  p->postTreeResp = inicializarTree();
  return p;
}
// Função que dá free a um Post.
void freePostsAtr(PostsAtr p){
    g_slist_free(p->datalistperg);
    g_slist_free(p->datalistres);
    g_slist_free(p->userPostlist);
    g_slist_free(p->nresplist);
    g_slist_free(p->respostalist);
    //g_tree_destroy(p->postTreeResp);
    free(p);
}
// Função que adiciona as respostas correspondentes a uma dada pergunta à arvore de respostas dessa mesma pergunta.
// Caso a pergutna ainda não exista ela cria-a.
void adicionaPostTreeRes(GHashTable* hashposts, PostsAtr pres){
    gpointer* foundvalue1 = NULL;
    if(g_hash_table_lookup_extended(hashposts,pres->parentId,NULL,(gpointer*)&foundvalue1)){
        PostsAtr pperg= (PostsAtr)foundvalue1; 
        Date data = chartodata((char*)pres->creationDate);

        gpointer * foundvalue2 = NULL;
        if(g_tree_lookup_extended(pperg->postTreeResp,data,NULL,(gpointer*)&foundvalue2)){
            PostsAtr pfoundres = (PostsAtr)foundvalue2;
            pfoundres->respostalist = g_slist_insert_before(pfoundres->respostalist,pfoundres->respostalist,pres);
          }
        else
            g_tree_insert(pperg->postTreeResp,data,pres);
    }

    else{
        PostsAtr newpperg = inicializaPostsAtr();
        Date data = chartodata((char*)pres->creationDate);
        g_tree_insert(newpperg->postTreeResp,data,pres);
        g_hash_table_insert(hashposts,pres->parentId,newpperg);
    }

}


// Função que ira ser aplicada a todos os elementos de uma lista de respostas e ir determinar qual a melhor resposta da lista.
void encontraMelhorRespostaList(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr pres = (PostsAtr) pi;
    UsersAtr u = g_hash_table_lookup(info->hashUsers,(char*)pres->ownerUserId);
    float result = (atoi((char*)pres->score)*(0.65)) + (atoi((char*)u->reputation) * (0.25)) + (atoi((char*)pres->commentCount) * (0.1)) ;
    if(info->resultado < result){
        info->resultado = result;
        info->id = atol((char*)pres->id);
      }
}
// Função que ira ser aplicada a todos os elementos de uma arvore de respostas e ir determinar qual a melhor resposta da arvore.
int encontraMelhorRespostaTreeaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr pres = (PostsAtr) pi;
    UsersAtr u = g_hash_table_lookup(info->hashUsers,(char*)pres->ownerUserId);
    float result = (atoi((char*)pres->score)*(0.65)) + (atoi((char*)u->reputation) * (0.25)) + (atoi((char*)pres->commentCount) * (0.1)) ;
    if(info->resultado < result){
        info->resultado = result;
        info->id = atol((char*)pres->id);
      }

    if(pres->respostalist!=NULL)
        g_slist_foreach(pres->respostalist,encontraMelhorRespostaList,info);

  return 0;
}
// Função que recebe uma arvore e uma estrutura Info e determina qual a melhor resposta de uma determinada arvore guardando-a na estrutura Info.
void encontraMelhorRespostaTree(GTree* tree, Info info){
    g_tree_foreach(tree,encontraMelhorRespostaTreeaux,info);
}
