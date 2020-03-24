#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <gmodule.h>
#include <hashUser.h>
#include <hashTag.h>

//função que dadas 2 datas devolve 1 caso a primeira seja maior que a segunda, -1 caso contrario e 0 caso sejam iguais.
gint my_comparatorDat(gconstpointer da1, gconstpointer da2) {
   Date d1 = (Date) da1;
   Date d2 = (Date) da2;
   gint i=0;

   if(testaDatamaior(d1,d2)) i = 1;
   if(testaDatamenor(d1,d2)) i = -1;
     if(testaDataIgual(d1,d2)) i = 0;

   return i;
}
//função que dadas 2 numeros de posts devolve -1 caso o primeiro seja maior que o segundo, 1 caso contrario e 0 caso sejam iguais.
gint my_comparatornPosts(gconstpointer n1a, gconstpointer n2b) {
	int n1 = n1a;
	int n2 = n2b;
   if(n1 > n2) return -1;
   if(n1 < n2) return 1;
   return 0;
}
//função que dadas 2 inteiros devolve -1 caso o primeiro seja maior que o segundo, 1 caso contrario e 0 caso sejam iguais.
gint my_comparatorMAQuestion(gconstpointer da1, gconstpointer da2) {
   int nresposta1 = da1;
   int nresposta2 = da2;
   if(nresposta1 > nresposta2) return -1;
   if(nresposta1 < nresposta2) return  1;
     return 0;
}
//função que dadas 2 inteiros devolve -1 caso o primeiro seja maior que o segundo, 1 caso contrario e 0 caso sejam iguais.
gint my_comparatorReputation(gconstpointer da1, gconstpointer da2) {
   UsersAtr u1 = (UsersAtr) da1;
   UsersAtr u2 = (UsersAtr) da2;
   if(u1->reputation > u2->reputation) return -1;
   if(u1->reputation < u2->reputation) return 1;
     return 0;
}
//função que dadas 2 inteiros devolve -1 caso o primeiro seja maior que o segundo, 1 caso contrario e 0 caso sejam iguais.
gint my_comparatorTagID(gconstpointer da1, gconstpointer da2) {
   int t1 =  da1;
   int t2 = da2;

   if(t1 > t2) return -1;
   if(t1 < t2) return 1;
    return 0;
}
// função que inicializa uma arvore ordenada por datas cronologicamente.
GTree* inicializarTree(){
   	return g_tree_new(my_comparatorDat);
}

GTree* inicializarTreePosts(){
	return g_tree_new(my_comparatornPosts);
}

GTree* inicializarTreeMAQuestion(){
	return g_tree_new(my_comparatorMAQuestion);
}

GTree* inicializarTreeOrdReputation(){
	return g_tree_new(my_comparatorReputation);
}
GTree* inicializarTreeTagOrdID(){
	return g_tree_new(my_comparatorTagID);
}
//função que dadas 2 datas testa se qual a menor.
gint testaDatamenor(Date a, Date b){
  gint i = 0;

  if (get_year(a) < get_year(b)) 
    i = 1;

  else if(get_year(a) == get_year(b)){
  
    if (get_month(a) < get_month(b)) 
      i = 1;
  
    else if (get_month(a) == get_month(b)){   
        
        if (get_day(a)<get_day(b))
          i = 1;
    }
  }
  return i; 
}
//função que dadas 2 datas testa se qual a maior.
gint testaDatamaior(Date a, Date b){
  gint i = 0;

  if (get_year(a) > get_year(b)) 
    i = 1;

  else if(get_year(a) == get_year(b)){
  
    if (get_month(a) > get_month(b)) 
      i = 1;
  
    else if (get_month(a) == get_month(b)){   
        
        if (get_day(a)>get_day(b))
          i = 1;
    }
  }
  return i; 
}
//função que dadas 2 datas testa se são iguais.
gint testaDataIgual(Date a, Date b){
    return (get_year(a) == get_year(b)) && (get_month(a) == get_month(b)) && (get_day(a) == get_day(b));
}
//função que dado uma String correspondente a uma data devolve uma estrutura Date correspondente a essa data.
Date chartodata (char* data){ 
    char aux[20];
    strcpy(aux,data);
     data = strtok(data,"T");
    int year = atoi(strtok(aux,"-"));
    int month = atoi(strtok(NULL, "-"));
    int day = atoi(strtok(NULL, "-"));
    Date datas = createDate(day,month,year);
    return datas;
}
//função que será aplicada a todos os elementos (Posts) de uma lista inserindo os primeiros N elementos noutra lista associada a estrutura Info.
void ForEachScoreList(gpointer value, gpointer data){
    Info info = (Info) data;
    PostsAtr p = (PostsAtr) value;
    
    if(info->N > 0){
    
     info->list = g_slist_insert_before(info->list,info->list,p);
     info->N--;
    //printf("%s ID: %s\n",(char*)p->score,(char*)p->id);
  }
}

//função que será aplicada a todos os elementos (Posts) de uma arvore  inserindo os primeiros N elementos noutra lista associada a estrutura Info.
int ForEachScoreTreeaux(gpointer key , gpointer value, gpointer data){
    Info info = (Info) data;
    PostsAtr p = (PostsAtr) value;

    g_slist_foreach(p->scorelist,ForEachScoreList,info);

     if(info->N <= 0) return 1;

  // printf("%s ID: %s\n",(char*)p->score,(char*)p->id);
     info->list = g_slist_insert_before(info->list,info->list,p);
     info->N--;
     return 0;
}
//função que dado uma arvore de elementos (Posts) ordenada por score e uma estrutura Info insere os primeiros N elementos da arvore na numa lista associada á estrutura Info.
void ForEachScoreTree(GTree* scoreTree, Info info){
	g_tree_foreach(scoreTree,ForEachScoreTreeaux,info);
}

//função que será aplicada a todos os elementos (Posts) de uma lista inserindo os primeiros N elementos noutra lista associada a estrutura Info.
void ForEachListMAQuestion(gpointer value, gpointer data){
    Info info = (Info) data;
    PostsAtr p = (PostsAtr) value;
    
    if(info->N > 0){
    
    info->list = g_slist_insert_before(info->list,info->list,p);
    info->N--;

     //printf("%d ID: %s\n",p->nrespostas,(char*)p->id);
  }
}
//função que será aplicada a todos os elementos (Posts) de uma arvore  inserindo os primeiros N elementos noutra lista associada a estrutura Info.
int ForEachTreeMAQuestionaux(gpointer key , gpointer value, gpointer data){
    Info info = (Info) data;
    PostsAtr p = (PostsAtr) value;

    g_slist_foreach(p->nresplist,ForEachListMAQuestion,info);

   //  printf("%d ID: %s\n",p->nrespostas,(char*)p->id);
    if(info->N > 0){
    info->list = g_slist_insert_before(info->list,info->list,p);
    info->N--;
   }
      if(info->N <= 0) return 1;
     return 0;
}
//função que dado uma arvore de elementos (perguntas) ordenada por nº de respostas  e uma estrutura Info insere os primeiros N elementos da arvore na numa lista associada á estrutura Info.
void ForEachTreeMAQuestion(GTree* tree, Info info){
    g_tree_foreach(tree,ForEachTreeMAQuestionaux,info);
}

//Função que dada uma String com várias tags e um estrutura Info, parte essa String nas várais tags e coloca-as numa hashtable associada à estrutura Info.
void treeinsereTagsOrdCount(char* tag, Info info){
    char aux[1000];
    strcpy(aux,tag);
    char* pt;
    pt = strtok (aux,"<>");

    while(pt!=NULL){
      
       tagAtr t = g_hash_table_lookup(info->hashtags,pt);

       gpointer* foundvalue = NULL;
       if(g_hash_table_lookup_extended(info->hash,(char*)t->tagname,NULL,(gpointer*)&foundvalue)){
            tagAtr foundtag = (tagAtr)foundvalue;
            foundtag->nused++;
       }
       else
            g_hash_table_insert(info->hash,(char*)t->tagname,t);

       pt = strtok (NULL,"<>");
  }
} 

//função que será aplicada a todos os elementos (Posts) de uma lista a fim de, caso esses post esteja num intervalo de tempo, insira as suas tags numa hashtable associada à estrutura info.
void foreachUserPostListNtag(gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    if(atoi((char*)p->postTypeId) == 1){

    Date data = chartodata((char*)p->creationDate);
    if(testaDatamenor(data,info->datai)) return 1;
    else if(!testaDatamaior(data,info->dataf))
         treeinsereTagsOrdCount((char*)p->tag,info);
    }
}
//função que será aplicada a todos os elementos (Posts) de uma arvore a fim de, caso esses post esteja num intervalo de tempo, insira as suas tags numa hashtable associada à estrutura info.
int foreachUserPostTreeNtag (gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    PostsAtr p = (PostsAtr) pi;
    if(atoi((char*)p->postTypeId) == 1){
    Date data = chartodata((char*)p->creationDate);
    if(testaDatamenor(data,info->datai)) return 1;
    else if(!testaDatamaior(data,info->dataf))
          treeinsereTagsOrdCount((char*)p->tag,info);
    }

    if(p->userPostlist!= NULL){
      g_slist_foreach(p->userPostlist,foreachUserPostListNtag,info);
      
    }
    return 0;
}
//função que será aplicada a todos os elementos de uma lista de posts a fim de guardar todas as tags de cada post numa hashtable associada à estrutura Info.
void foreachOrdUserRepList(gpointer pi, gpointer inf){
    Info info = inf;
    UsersAtr u = (UsersAtr) pi;
    if(info->N > 0){ 
        info->N--;
    g_tree_foreach(u->userPostTree,foreachUserPostTreeNtag,info);
  }
}
//função que será aplicada a todos os elementos de uma arvore de posts a fim de guardar todas as tags de cada post numa hashtable associada à estrutura Info.
int foreachOrdUserRepTreeaux (gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    UsersAtr u = (UsersAtr) pi;

    if(info->N<=0) return 1; 
    g_tree_foreach(u->userPostTree,foreachUserPostTreeNtag,info);
       info->N--;

  if(u->userOrdReputionlist != NULL);
        g_slist_foreach(u->userOrdReputionlist,foreachOrdUserRepList,info);
    return 0;
  }
//Função que recebe uma Tree de listas de users ordenados por reputação e irá guardar numa hashtable associada à estrutura Info, todas as tags de todos utilizadores, contando o nº de vezes que foram usadas (cada uma).
 void foreachOrdUserRepTree(GTree* tree, Info info){
    g_tree_foreach(tree,foreachOrdUserRepTreeaux,info);
  }
// Função que será aplciada a todos os elementos de uma hashtable de modo a inserir ordenadamente (pelo ñº de vezes usada) cada tag da hash, numa arvore.
  void forEachNTagHashaux (gpointer id, gpointer pi, gpointer inf){
    Info info = inf;
    tagAtr t = (tagAtr) pi;
    
      gpointer* foundvalue = NULL;
        if(g_tree_lookup_extended(info->tree2,(gpointer*)t->nused,NULL,(gpointer*)&foundvalue)){
            tagAtr foundtag = (tagAtr)foundvalue;
            foundtag->tagsamecountlist = g_slist_insert_before(foundtag->tagsamecountlist,foundtag->tagsamecountlist,t);
        }
        else g_tree_insert(info->tree2,(gpointer*)t->nused,t);
}
// função que dado uma hashtbale que contem tags e uma estrutura info, insere ordenadamente (pelo ñº de vezes usada) todas essas tags da hash numa arvore  associada à estrutura Info.
void forEachNTagHash (GHashTable* hash, Info info){
    g_hash_table_foreach(hash,forEachNTagHashaux,info);
}
// funçao que será aplciada a todos os elementos de uma hash de tags a fim de resetar n nº de vezes que esta foi usada.
  void resetnusedaux(gpointer key , gpointer value, gpointer data){
    tagAtr t = (tagAtr) value;
    t->nused = 0;
}
//função que recebe uma hash de tags e reseta o nº de vezes que cada tag foi usada.
void resetnused(GHashTable* hash){
      g_hash_table_foreach(hash,resetnusedaux,NULL);
}

//função que será aplicada a todos os elementos de uma lista a fim de inserir cada elemento desssa lista noutra lista.
  void forEachNTagList (gpointer pi, gpointer inf){
    Info info = inf;
    tagAtr t = (tagAtr) pi;
    info->list = g_slist_insert_before(info->list,info->list,t);
       //printf("tad id %s  tag count %d name: %s\n",(char*)t->id, t->nused, (char*)t->tagname);
}
//função que será aplicada a todos os elementos de uma arvore a fim de inserir cada elemento desssa arvore numa lista.
int forEachNTagTreeaux(gpointer id, gpointer pi, gpointer inf){ 
    Info info = inf;
    tagAtr t = (tagAtr) pi;
       // printf("tad id %s  tag count %d name: %s\n",(char*)t->id, t->nused, (char*)t->tagname);
        info->list = g_slist_insert_before(info->list,info->list,t);
        if(t->tagsamecountlist != NULL){
           g_slist_foreach(t->tagsamecountlist,forEachNTagList,info);
          }
    return 0;

}

GHashTable* inicializahash(){
    g_hash_table_new(g_str_hash, g_str_equal);
}
//função que recebe uma arvore e uma Info a qual irá inserir todas as tags da arvore numa lista associada à Info.
void forEachNTagTree(GTree* tree, Info info){
    g_tree_foreach(info->tree2,forEachNTagTreeaux,info);
} 
//função que recebe uma Info e liberta a sua memoria.
void freeInfo(Info info){
    free(info);
  }
