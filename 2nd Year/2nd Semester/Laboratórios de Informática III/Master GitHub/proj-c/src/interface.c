#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include <interface.h>
#include <hashUser.h>
#include <treeRespostas.h>
#include <hashTag.h>

#define VAZIO NULL

struct TCD_community {
    GHashTable* hashPosts;      // hashtable que armazena todos os posts
    GHashTable* hashUsers;      // hashtabçe que armazena todos os users
    GHashTable* hashTags;     // hashtable que armazena todas as tags
    GTree *nUserPoststree;   // tree de users ordenada por nº de posts
    GTree *treePerg;			//arvore com todas as perguntas ordenada por datas
    GTree *treeRes;			//arvore com todas as respostas ordenada por datas
};
//definição da estrutura TAD_community;
TAD_community init() {
  
    TAD_community h = (TAD_community) malloc(sizeof(struct TCD_community));  
    h->hashPosts = inicializaPostHashtable();
    h->hashUsers = inicializaUserHashtable();
    h->hashTags = inicializaTagHashtable();
    h->nUserPoststree = inicializarTreePosts();
    h->treePerg = inicializarTree();
    h->treeRes = inicializarTree();
    return h;
}
// função que dá load dos ficheiros .xml para a estrutura TAD_community.
TAD_community load(TAD_community com, char* dump_path){
        char tags[100]; 
        char posts[100];
        char users[100]; 
    if(dump_path != NULL){
    strcpy(posts,dump_path); 
    strcpy(users,dump_path); 
    strcpy(tags,dump_path);
    strcat(posts,"/Posts.xml");
    strcat(tags,"/Tags.xml");
    strcat(users,"/Users.xml");
    }
    else{
    strcpy(posts,"Posts.xml"); 
    strcpy(users,"Users.xml"); 
    strcpy(tags,"Tags.xml");
    }

   printf("Parser START\n");
  parseDocs (users,com->hashPosts,com->hashUsers,com->hashTags,com->treePerg,com->treeRes);
  parseDocs (posts,com->hashPosts,com->hashUsers,com->hashTags,com->treePerg,com->treeRes);
  parseDocs (tags,com->hashPosts,com->hashUsers,com->hashTags,com->treePerg,com->treeRes);
  initnUserPoststree(com->hashUsers,com->nUserPoststree);
  printf("Parser concluido\n");

  return 0;
}
// funçao que dado o identificador de um post retorna o titulo e o nome do utilizador do autor.
STR_pair info_from_post(TAD_community com, long id){
  char j[20];
  sprintf(j,"%ld",id);
  PostsAtr p = g_hash_table_lookup(com->hashPosts,j);
  UsersAtr u;
  if(strcmp((char*)p->postTypeId,"2") != 0)
  u = g_hash_table_lookup(com->hashUsers,p->ownerUserId);
  else{
     p = g_hash_table_lookup(com->hashPosts,(char*)p->parentId);
     u = g_hash_table_lookup(com->hashUsers,p->ownerUserId);
  }
  STR_pair par = create_str_pair((char*)u->displayName,(char*)p->title);
  printf("titulo%s nome %s\n, com %d posts", (char*)p->title,(char*) u->displayName,u->nposts);
  return par;
}
// Função que dado um N obtem o top N utilizadores com maior numero de posts de sempre
LONG_list top_most_active(TAD_community com, int N){
    LONG_list l;
    l = create_list(N);
    Info info = (Info) malloc(sizeof(struct Info));
    info->N = N;
    info->list = NULL;
    UsersAtr u;
    TreeGetfirstNUsers(com->nUserPoststree,info);
    int test = g_slist_length(info->list);
    if(test<N) N = test;
    N=N-1;
   while(N>=0){
        u = g_slist_nth_data(info->list,N);
        set_list(l,N,atol((char*)u->id));
        printf("UserID: %ld com %d posts \n", get_list(l,N),u->nposts);
        N--;
    }
    freeInfo(info);
    g_slist_free(info->list);
    return l;
}
//função que Dado um intervalo de tempo4 arbitrario obtem o numero total de posts 
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    LONG_pair par;
    Info info = (Info) malloc(sizeof(struct Info));
    info->datai = begin;
    info->dataf = end;
    info->rescount = 0;
    info->pergcount = 0;
    TreeForEachResTotalPosts(com->treeRes,info);
    TreeForEachPergTotalPosts(com->treePerg,info);
    par = create_long_pair(info->rescount,info->pergcount);
    printf("RES ::%ld  PERGG::: %ld\n", get_fst_long(par), get_snd_long(par) );
    freeInfo(info);
    return par;
}
//função que Dado um intervalo de tempo arbitrario, retorna todasas perguntas contendo uma determinada tag.
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    char aux[100] = "<";
    strcat(aux,tag);
    strcat(aux,">");
    tag = aux;
    LONG_list l;
    Info info = (Info) malloc(sizeof(struct Info));
    info->datai = begin;
    info->dataf = end;
    info->list = NULL;
    info->tag= tag;
    info->tagcount = 0;
    TreeForEachPergTag(com->treePerg,info);
    int i = 0;
    int ks = g_slist_length (info->list);
    l = create_list(ks);
    PostsAtr p;
    while(i<ks){
       p = g_slist_nth_data(info->list,i);
       set_list(l,i,atol((char*)p->id));
       printf("%ld tag data: %s\n",get_list(l,i), (char*)p->creationDate );
        i++;
    }
    freeInfo(info);
    g_slist_free(info->list);
    return l;
}
//função que Dado um ID de utilizador, devolve a informacao dos eu perfil (short bio) e os IDs dos seus 10 ultimos posts
USER get_user_info(TAD_community com, long id){
    USER user;
    Info info = (Info) malloc(sizeof(struct Info));
    info->N = 0;
    char j[20];
    sprintf(j,"%ld",id);
    UsersAtr u = g_hash_table_lookup(com->hashUsers,j);
    TreeForEachUserInfo(u->userPostTree,info);
    printf("%s\n", (char*)u->aboutMe);
    user = create_user((char*)u->aboutMe,(info->ids));
    freeInfo(info);
    return user;
}

//função que Dado um intervalo de tempo arbitrario, devolve os IDs das N respostas com mais votos, em ordem decrescente do numero de votos
LONG_list most_voted_answers(TAD_community com, int N, Date begin,Date end){
    LONG_list l;
    l = create_list(N);
    Info info = (Info) malloc(sizeof(struct Info));
    info->datai = begin;
    info->dataf = end;
    info->tree = createScoreTree();
    info->list = NULL;
    info->N = N;
    TreeForEachResVotes(com->treeRes,info);
    ForEachScoreTree(info->tree,info);
    PostsAtr p;
    int test = g_slist_length(info->list);
    if(test<N) N = test;
    N=N-1;
    while(N>=0){
        p = g_slist_nth_data(info->list,N);
        set_list(l,N,atol((char*)p->id));
        printf("%s ID: %ld\n",(char*)p->score,get_list(l,N));
        N--;
    }
    resetscorelist(info->tree);
    freeInfo(info);
    g_tree_destroy(info->tree);
    g_slist_free(info->list);
    return l;

}
// função que Dado um intervalo de tempo arbitrario, devolve as IDs das N perguntas com mais respostas, em ordem decrescente do numero de respostas.

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    LONG_list l;
    l = create_list(N);
    Info info = (Info) malloc(sizeof(struct Info));
    info->datai = begin;
    info->dataf = end;
    info->tree = inicializarTreeMAQuestion();
    info->N = N;
    info->hashposts = com->hashPosts;
    info->rescount = 0;
    info->list = NULL;
    TreeForEachResMostPerg(com->treePerg,info);
    ForEachTreeMAQuestion(info->tree,info);
    PostsAtr p;
    int test = g_slist_length(info->list);
    if(test<N) N = test;
    printf("N:%d\n",N );
    N=N-1;
   while(N>=0){
        p = g_slist_nth_data(info->list,N);
        printf(" ID: %s com  %d repostas\n",(char*)p->id, p->nrespostas );
        set_list(l,N,atol((char*)p->id));
        N--;
    }
    resetnresplist(info->tree);
    freeInfo(info);
    g_tree_destroy(info->tree);
    g_slist_free(info->list);
    return l;
}
// função que Dado uma palavra, devolve uma lista com os IDs de N perguntas cujos tıtulos a contenham, ordenados por cronologia inversa;
LONG_list contains_word(TAD_community com, char* word, int N){
    LONG_list l;
    l = create_list(N);
    Info info = (Info) malloc(sizeof(struct Info));
    info->N = N;
    info->word = word;
    info->list = NULL;
    TreeForEachPergTitle(com->treePerg,info);
    int i = 0;
    PostsAtr p;
    int test = g_slist_length(info->list);
    if(test<N) N = test;
    while(i<N){
        p = g_slist_nth_data(info->list,i);
        printf("%s , %s\n",(char*)p->id,(char*)p->creationDate );
        set_list(l,i,atol((char*)p->id));
        i++;
    }
    freeInfo(info);
    g_slist_free(info->list);
    return l;
}
// função que Dados os IDs de dois utilizadores, devolve as ultimas N perguntas (cronologia inversa) em que participaram dois utilizadores especıficos
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    char sid1[20], sid2[20];
    sprintf(sid1,"%ld",id1);
    sprintf(sid2,"%ld",id2);
    LONG_list l = create_list(N);
    UsersAtr u1 = g_hash_table_lookup(com->hashUsers,sid1);
    UsersAtr u2 = g_hash_table_lookup(com->hashUsers,sid2);
    Info info = (Info) malloc(sizeof(struct Info));
    info->u1 = u1;
    info->post2 = NULL;
    info->list = NULL;
    info->N = 0;
    info->hashposts = com->hashPosts;
    forEachTreeBothP1(u2->userPostTree,info);
    int i = 0;
    PostsAtr p;
     while(i<N && i< g_slist_length(info->list)){
        p = g_slist_nth_data(info->list,i);
        printf("POST ID %s\n",(char*)p->id );
        set_list(l,i,atol((char*)p->id));
        i++;
    }
    freeInfo(info);
    g_slist_free(info->list);
    return l;
}
//funçao que Dado o ID de uma pergunta, obter a melhor resposta.
long better_answer(TAD_community com, long id){
    char j[20];
    sprintf(j,"%ld",id);
    Info info = (Info) malloc(sizeof(struct Info));
    info->resultado = 0;
    info->id = 0;
    info->hashUsers = com->hashUsers;
    PostsAtr p = g_hash_table_lookup(com->hashPosts,j);
    encontraMelhorRespostaTree(p->postTreeResp,info);
    long lid = info->id;
    if(lid == 0) {
      printf("ID :-1\n");
      freeInfo(info);
      return -1;
    }
    else{
      printf("ID :%ld\n",info->id );
      freeInfo(info);
      return lid;
    }
}
//funçãoo que Dado um intervalo arbitrario de tempo, devolver os identificadores das N tags mais usadas pelos N utilizadores com melhor reputacao
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    LONG_list l = create_list(N);
    Info info = (Info) malloc(sizeof(struct Info));
    info->datai = begin;
    info->dataf = end;
    info->tree = createScoreTree();
    info->tree2 = inicializarTreeTagOrdID();
    info->N = N;
    info->list = NULL;
    info->hash = inicializahash();
    info->hashtags = com->hashTags;
    info->hashUsers = com->hashUsers;
    TreeForEachPergReputation(com->treePerg,info);
    foreachOrdUserRepTree(info->tree,info);
    forEachNTagHash (info->hash,info);
    forEachNTagTree(info->tree2,info);
    info->list = g_slist_reverse(info->list);
    int i = 0;
    tagAtr t;
    int test = g_slist_length(info->list);
    if(test<N) N = test;
    while(i<N){
        t = g_slist_nth_data(info->list,i);
        printf("tag id :%s\n", (char*)t->id);
        set_list(l,i,atol((char*)t->id));
        i++;
    }
    resetuserOrdReputionlist(info->tree);
    resetnused(info->hash);
    freeInfo(info);
    g_tree_destroy(info->tree);
    g_tree_destroy(info->tree2);
    g_hash_table_destroy(info->hash);

    return l;
}

TAD_community clean(TAD_community com){
    g_hash_table_destroy(com->hashPosts);
    g_hash_table_destroy(com->hashUsers);
    g_hash_table_destroy(com->hashTags);
    g_tree_destroy(com->nUserPoststree);
    g_tree_destroy(com->treePerg);
    g_tree_destroy(com->treeRes);
    free(com);
    return com;
}