#include <stdio.h>
#include <stdlib.h>
#include <hashUser.h>
#include <treePerguntas.h>
#include <string.h>
// Função que será aplicada para todos os elementos (posts) de uma arvore e irá incrementar um contador da Info caso esse post esteja num intervalo de tempo definido o qual tambem está na Info.
int TreeForEachPergaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamaior(data,info->dataf)) return 1;
    else if(!testaDatamenor(data,info->datai)) 
         info->pergcount += p->ndataigual;
        return 0;
}
//dado uma arvore de perguntas e uma Info, conta quantos posts existem no intervalo de tempo dado.
void TreeForEachPergTotalPosts(GTree* treePerg, Info info){
	g_tree_foreach(treePerg,TreeForEachPergaux,info);
}

//função que dadas 2 datas compara devolvendo -1 se a primeira data for maior , 1 caso contrario e 0 caso sejam iguais.
int my_comparatorTag(gconstpointer d1a, gconstpointer d2a){
    PostsAtr p1 = (PostsAtr) d1a;
    PostsAtr p2 = (PostsAtr) d2a;
    Date d1 = chartodata((char*)p1->creationDate);
    Date d2 = chartodata((char*)p2->creationDate);

    if(testaDatamaior(d1,d2)) return -1;
    if(testaDataIgual(d1,d2)) return 0;
    return 1;
}
//função que irá ser aplicada a todos os elementos (perguntas) de uma lista   colocando na lista da Info  o elemento da lista caso contenha uma determinada tag.
void ListForEachPergTag(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
        info->tagcount++;
    if(strstr((char*)p->tag,info->tag)!=NULL){
    info->list = g_slist_insert_sorted(info->list,p,my_comparatorTag);
  }
}
//função que irá ser aplicada a todos os elementos (perguntas) de uma arvore compreendidos entre uma determinada data e irá colocar na lista da Info caso o elemento da arvore contenha uam determinada tag.
int TreeForEachPergTagaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamaior(data,info->dataf)) return 1;
    else if(!testaDatamenor(data,info->datai)){

         if(strstr((char*)p->tag,info->tag)!=NULL){ 
            info->list = g_slist_insert_sorted(info->list,p,my_comparatorTag);
          }
        g_slist_foreach(p->datalistperg,ListForEachPergTag,info);
    }
    return 0;
}

//função que dado uma arvore de perguntas coloca na lista da Info todas as perguntas que contênham uma determinada tag.
void TreeForEachPergTag(GTree* treePerg, Info info){
    g_tree_foreach(treePerg,TreeForEachPergTagaux,info);
}

//função que será aplicada a todos os elementos (posts), que estiverem compriendidos entre determindada data, de uma lista a fim de contar quantas respostas tem um post.
void ContaRespostasNaDataList(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamaior(data,info->dataf)) return;
    if(!testaDatamenor(data,info->datai)) {
        info->rescount++;}
}
//função que será aplicada a todos os elementos (posts), que estiverem compriendidos entre determindada data, de uma arvore a fim de contar quantas respostas tem um post.
int ContaRespostasNaDataTree(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamaior(data,info->dataf)) return 1;
    if(!testaDatamenor(data,info->datai))
        info->rescount++;
        if(p->respostalist!=NULL)
            g_slist_foreach(p->respostalist,ContaRespostasNaDataList,info);
          return 0;
    }
// funçao que dada um post reseta a sua nresplist.
int resetnresplistaux(gpointer key , gpointer value, gpointer data){
    PostsAtr p = (PostsAtr) value;
    //g_slist_free (p->scorelist);
    p->nresplist = NULL;
    return 0;
}
//função que dado uma arvore de posts a nresplist de todos os posts da arvore.
void resetnresplist(GTree* tree){
      g_tree_foreach(tree,resetnresplistaux,NULL);
}
//função que será aplciada a todos os elementos (perguntas) de uma lista de modo a contar todas as respostas de cada pergunta. 
void ListForEachMostAnsweredPerg(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
          info->rescount = 0;
          g_tree_foreach(p->postTreeResp,ContaRespostasNaDataTree,info);
            p->nrespostas = info->rescount;
              gpointer* foundvalue = NULL;          
          if(g_tree_lookup_extended(info->tree,p->nrespostas,NULL,(gpointer*)&foundvalue)){
              PostsAtr post = (PostsAtr)foundvalue;
              post->nresplist = g_slist_insert_before(post->nresplist,post->nresplist,p);
            }
          else
            g_tree_insert(info->tree,p->nrespostas,p);
          
  }

//função que será aplciada a todos os elementos (perguntas) de uma arvore de modo a contar todas as respostas de cada pergunta. 
int TreeForEachResMostPergaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamaior(data,info->dataf)) return 1;
    else if(!testaDatamenor(data,info->datai)) {
          info->rescount = 0;
          g_tree_foreach(p->postTreeResp,ContaRespostasNaDataTree,info);
          p->nrespostas = info->rescount;

          gpointer* foundvalue = NULL;          
          if(g_tree_lookup_extended(info->tree,p->nrespostas,NULL,(gpointer*)&foundvalue)){
              PostsAtr post = (PostsAtr)foundvalue;
              post->nresplist = g_slist_insert_before(post->nresplist,post->nresplist,p);
            }
          else
            g_tree_insert(info->tree,p->nrespostas,p);
            if(p->datalistperg!=NULL)
                g_slist_foreach(p->datalistperg,ListForEachMostAnsweredPerg,info);
            // info->list = g_slist_insert_sorted(info->list,p,my_comparatorVotes);
          }
    return 0;
}
//função que recebe a arvore de respostas e uma Info e conta quantas respostas tem cada pergunta de terminado intervalo de tempo, inserindo-as ordenadamente pelo numero de respostas, numa lista associada à estrutura Info.
void TreeForEachResMostPerg(GTree* treePerg, Info info){
	g_tree_foreach(treePerg,TreeForEachResMostPergaux,info);
}


//função que compara as datas de 2 posts, retornando -1 caso a data do primeiro post seja maior do que a data do segundo, 1 caso contraio e 0 se forem iguais.
int  my_comparatorPergTitle(gconstpointer d1a, gconstpointer d2a){
    PostsAtr p1 = (PostsAtr) d1a;
    PostsAtr p2 = (PostsAtr) d2a;
    Date d1 = chartodata((char*)p1->creationDate);
    Date d2 = chartodata((char*)p2->creationDate);

    if(testaDatamaior(d1,d2)) return -1;
    if(testaDataIgual(d1,d2)) return 0;
    return 1;
}
//função que será aplicada a todos os elementos(perguntas) de uma arvore para determinar se estes cotêm determinda palavra ou não, caso sim, inserir a pergunta na lista da Info.
void ListForEachPergTitle(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    
    if(info->N > 0)
    	if(strstr((char*)p->title,info->word)!=NULL){ 
        	info->list = g_slist_insert_sorted(info->list,p,my_comparatorPergTitle);
    }   
}
//função que será aplicada a todos os elementos(perguntas) de uma arvore para determinar se estes cotêm determinda palavra ou não, caso sim, inserir a pergunta na lista da Info.
int TreeForEachPergTitleaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    if(strstr((char*)p->title,info->word)!=NULL){

        info->list = g_slist_insert_sorted(info->list,p,my_comparatorPergTitle);
    }
    if(info->N <= 0) return 1;
    if(p->datalistperg!=NULL){
        g_slist_foreach(p->datalistperg,ListForEachPergTitle,info);
    }
    return 0;
}
// funçao que dada a arvore de todas as perguntas vai verificar que perguntas contêm determinada palavra e colocar na lista da Info esses mesmo posts ordenados por cronologia inversa.
void TreeForEachPergTitle(GTree* treePerg, Info info){
	g_tree_foreach(treePerg,TreeForEachPergTitleaux,info);
}


//Função que será aplicada a todos os elementos (posts) de uma lista de modo a encontrar o seu owner e inseri-lo noutra lista ordenada por reputação.
void ListForEachPergReputation(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
         UsersAtr u = g_hash_table_lookup(info->hashUsers,(char*)p->ownerUserId);
         if(!u->added){

          gpointer* foundvalue = NULL;   
          if(g_tree_lookup_extended(info->tree,(char*)u->reputation,NULL,(gpointer*)&foundvalue)){   
              UsersAtr user = (UsersAtr)foundvalue;
              user->userOrdReputionlist = g_slist_insert_before(user->userOrdReputionlist,user->userOrdReputionlist,u);
              u->added = 1;
          }
          else{
              g_tree_insert(info->tree,(char*)u->reputation,u);
              u->added = 1;
          }
          
      }
}

//Função que será aplicada a todos os elementos (posts) de uma arvore de modo a encontrar o seu owner e inseri-lo numa lista ordenada por reputação.
int TreeForEachPergReputationaux(gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    Date data = chartodata((char*)p->creationDate);
  if(testaDatamaior(data,info->dataf)) return 1;
    else if(!testaDatamenor(data,info->datai)){

         UsersAtr u = g_hash_table_lookup(info->hashUsers,(char*)p->ownerUserId);
         if(!u->added){

          gpointer* foundvalue = NULL;   
          if(g_tree_lookup_extended(info->tree,(char*)u->reputation,NULL,(gpointer*)&foundvalue)){   
              UsersAtr user = (UsersAtr)foundvalue;
              user->userOrdReputionlist = g_slist_insert_before(user->userOrdReputionlist,user->userOrdReputionlist,u);
              u->added = 1;
          }
          else{
              g_tree_insert(info->tree,(char*)u->reputation,u);
              u->added = 1;
          }              
        }
            if(p->datalistperg!=NULL)
             g_slist_foreach(p->datalistperg,ListForEachPergReputation,info);
         
        }
    return 0;
}
//dado uma arvore de de posts, caso estes estejam em determinada data, colcoa na lista Info todos os criadores dos posts ordenados por reputação.
void TreeForEachPergReputation(GTree* treeper, Info info){
    g_tree_foreach(treeper,TreeForEachPergReputationaux,info);
  }
//funçao que reseta a userOrdReputionlist de um user.
  int resetuserOrdReputionlistaux(gpointer key , gpointer value, gpointer data){
    UsersAtr u = (UsersAtr) value;
    //g_slist_free (p->scorelist);
    u->userOrdReputionlist = NULL;
    return 0;
}
//funçao que recebe uma arvore de users e reseta a userOrdReputionlist de todos os elementos dessa arvore.
void resetuserOrdReputionlist(GTree* tree){
      g_tree_foreach(tree,resetuserOrdReputionlistaux,NULL);
}
