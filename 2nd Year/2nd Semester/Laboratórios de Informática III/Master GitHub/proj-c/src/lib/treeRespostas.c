#include <stdio.h>
#include <stdlib.h>
#include <hashPost.h>
#include <treeRespostas.h>
//funçaõ que será aplciada a todos os elementos de uma arvore de modo a contar todas as respostas dessa arvore que ocorreram num intervalo de tempo.
int TreeForEachResaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamaior(data,info->dataf)) return 1; 
    else if(!testaDatamenor(data,info->datai)) {

          info->rescount += p->ndataigual;
}
        return 0;
    
}
//funçaõ recebe uma arvore, uma Info e conta todas as respostas dessa arvore que ocorreram num intervalo de tempo colcoando a o resultado na Info-
void TreeForEachResTotalPosts(GTree* treeRes, Info info){
    g_tree_foreach(treeRes,TreeForEachResaux,info);
}

//funçaõ que recebe 2 scores e os compara, retorna 1 caso o primeiro seja menor que o segundo, -1 caso contrario e 0 caso sejam iguais.
gint my_comparatorScore(gconstpointer da1, gconstpointer da2) {
   int score1 = atoi((char*) da1);
   int score2 = atoi((char*) da2);
   if(score1 > score2) return -1;
   if(score1 < score2) return  1;
     return 0;
}
//funçaõ que compara o nº de vosots de 2 posts, retorna 1 caso o primeiro seja menor que o segundo e -1 caso contrario; 
int my_comparatorVotes(gconstpointer d1a, gconstpointer d2a){
    PostsAtr p1 = (PostsAtr) d1a;
    PostsAtr p2 = (PostsAtr) d2a;

    if(atoi((char*)p1->score) > atoi((char*)p2->score)) return -1;
    //if(atoi((char*)p1->score) == atoi((char*)p2->score)) return 0;
return 1;
}
//funçao que inicializa uma arvore ordenada por score.
GTree* createScoreTree(){
  return g_tree_new(my_comparatorScore);
}
//frunçaºo que reseta a scorelist de um post
int freelisttreeaux(gpointer key , gpointer value, gpointer data){
    PostsAtr p = (PostsAtr) value;
    p->scorelist = NULL;
    return 0;
}
//funçaõ que reseta a score list de todos os elementos de uma tree.
void resetscorelist(GTree* tree){
      g_tree_foreach(tree,freelisttreeaux,NULL);
}
//funçaõ que ira ser aplicada a todos os elementos de uma lista para inserir na arvore da info todas as respostas compreendidas numa determinada data ordenadas por nº de votos.
void ListForEachResVotes(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    gpointer* foundvalue = NULL;          
        if(g_tree_lookup_extended(info->tree,(char*)p->score,NULL,(gpointer*)&foundvalue)){
            PostsAtr post = (PostsAtr)foundvalue;
            post->scorelist = g_slist_insert_before(post->scorelist,post->scorelist,p);
          }
        else g_tree_insert(info->tree,(char*)p->score,p);
    //printf("olaa\n");
}
//funçaõ que ira ser aplicada a todos os elementos de uma arvore para inserir na arvore da info todas as respostas compreendidas numa determinada data ordenadas por nº de votos.
int TreeForEachResVotesaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamaior(data,info->dataf)) return 1;
    else if(!testaDatamenor(data,info->datai)){
          
          gpointer* foundvalue = NULL;      

          if(g_tree_lookup_extended(info->tree,(char*)p->score,NULL,(gpointer*)&foundvalue)){   
              PostsAtr post = (PostsAtr)foundvalue;
              post->scorelist = g_slist_insert_before(post->scorelist,post->scorelist,p);
            }
          else
            g_tree_insert(info->tree,(char*)p->score,p);
            
            if(p->datalistres!=NULL)
             g_slist_foreach(p->datalistres,ListForEachResVotes,info);
          }
    return 0;
}
//funçaõ que recebe uma arvore e uma Info e insere na arvore da info todas as respostas compreendidas numa determinada data ordenadas por nº de votos.
void TreeForEachResVotes(GTree* treeRes, Info info){
	g_tree_foreach(treeRes,TreeForEachResVotesaux,info);
}
// funão que ira ser aplicada a todos os elementos de uma lista de modo a contar o nº de respostas de cada pergunta.
void ListForEachMostAnsweredRes(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    gpointer* foundvalue = NULL;

        if(g_hash_table_lookup_extended(info->hashposts,(char*)p->parentId,NULL,(gpointer*)&foundvalue)){
            PostsAtr post = (PostsAtr)foundvalue;
            post->nrespostas ++;
          }    
}
