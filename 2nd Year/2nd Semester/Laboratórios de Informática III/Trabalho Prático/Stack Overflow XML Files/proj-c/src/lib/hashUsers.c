#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <hashUser.h>
#include <date.h>

#define VAZIO NULL
//funçao que inicializa a hashtable dos users.
GHashTable* inicializaUserHashtable(){
    return g_hash_table_new_full(g_str_hash, g_str_equal,free,freeUsersAtr);
}

//funçao que compara 2 datas, retornando -1 caso a primeira seja maior que a segunda, 1 caso contraio, 0 caso sejam iguais.
gint my_comparatorDatInv(gconstpointer da1, gconstpointer da2) {
   Date d1 = (Date) da1;
   Date d2 = (Date) da2;
   gint i=0;
   if(testaDatamaior(d1,d2)) i = -1;
   if(testaDatamenor(d1,d2)) i = 1;
   if(testaDataIgual(d1,d2)) i = 0;
   return i;
}
//função que inicializa a estrutura dos users com todos os parametros necessarios para todas as querys.
UsersAtr inicializaUsersAtr(){
  UsersAtr u = (UsersAtr) malloc(sizeof(struct UsersAtr));
  u->id = (xmlChar*)VAZIO;
  u->displayName = (xmlChar*)VAZIO;
  u->aboutMe = (xmlChar*)VAZIO;
  u->reputation = (xmlChar*)VAZIO;
  u->userPostTree = g_tree_new(my_comparatorDatInv);
  u->nposts = 0;
  u->npostslist = VAZIO;
  u->userOrdReputionlist = VAZIO;
  u->added = 0;
  return u;
}

//funçao que liberta a memoria do UsersAtr.
void freeUsersAtr(UsersAtr u){
    g_tree_destroy(u->userPostTree);
    g_slist_free(u->npostslist);
    g_slist_free(u->userOrdReputionlist);
    free(u);
}

//função que conta o numero de posts de cada user.
void adicionaUsernPosts(GHashTable* HashUsers, char* id){
  UsersAtr u = g_hash_table_lookup(HashUsers,id);
  u->nposts += 1;
}
//função que adiciona que cria a arvore de posts de cada user.
void adicionaUserPosttree(GHashTable* HashUsers, char* id, PostsAtr p, Date data){
  UsersAtr u = g_hash_table_lookup(HashUsers,id);
        gpointer* foundvalue = NULL;
          if(g_tree_lookup_extended(u->userPostTree,data,NULL,(gpointer*)&foundvalue)){
            
              PostsAtr post= (PostsAtr)foundvalue;
              post->userPostlist = g_slist_insert_before(post->userPostlist,post->userPostlist,p);
          }
        else {
          g_tree_insert(u->userPostTree,data,p);
              }
}
//função que sera aplicada a todos os elementos de uma lista de modo a colocar na Info os 10 posts mais recentes da lista.
void ForEachUserInfoList(gpointer value, gpointer data){
    Info info = (Info) data;
    PostsAtr p = (PostsAtr) value;
    
    if(info->N<10){
      info->ids[info->N] = atol((char*)p->id);
      info->N ++;
     printf("%s ID: %s\n",(char*)p->id,(char*)p->creationDate);
  }
}
//função que sera aplicada a todos os elementos de uma arvore de modo a colocar na Info os 10 posts mais recentes da arvore.
int TreeForEachUserInfoaux(gpointer data, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
      
     printf("%s ID: %s\n",(char*)p->id,(char*)p->creationDate);
      info->ids[info->N] = atol((char*)p->id);
      info->N ++;
      g_slist_foreach(p->userPostlist,ForEachUserInfoList,info);
     if(info->N>=10) return 1;

    return 0;
}
//função que dada uma arvore coloca na Info os 10 posts mais recenetes dessa lista.
void TreeForEachUserInfo(GTree* userPostTree, Info info){
    g_tree_foreach(userPostTree,TreeForEachUserInfoaux,info);
  }