
#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <libxml/parser.h>
#include <date.h>
#include <list.h>

typedef struct UsersAtr *UsersAtr;
typedef struct PostsAtr *PostsAtr;

typedef struct Info{
    Date datai;
    Date dataf;
    int N;
    long rescount;
    long pergcount;
    char *tag;
    int tagcount;
    GSList* list;
    long ids[10];
    GTree* tree;
    GTree* tree2;
    GHashTable* hashposts;
    GHashTable* hashUsers;
    GHashTable* hashtags;
    char *word;
    UsersAtr u1;
    PostsAtr post2;
    PostsAtr foundpost;
    GHashTable* hash;
    long id;
    float resultado;
}* Info;

int testaDatamenor(Date a, Date b);
int testaDatamaior(Date a, Date b);
int testaDataIgual(Date a, Date b);
Date chartodata (char* data);
void ForEachScoreTree(GTree* Tree, Info info);
void ForEachTreeMAQuestion(GTree* tree, Info info);
GTree* inicializarTreeOrdReputation();
GTree* inicializarTreeMAQuestion();
GTree* inicializarTreePosts();
GTree* inicializarUserTree();
GTree* inicializarPostTree();
GTree* inicializarTreeTagOrdID();
GTree* inicializarTree();
GHashTable* inicializahash();
void foreachOrdUserRepTree(GTree* tree, Info info);
void forEachNTagHash (GHashTable* hash, Info info);
void forEachNTagTree(GTree* tree, Info info);
void resetnused(GHashTable* hash);
void freeInfo(Info info);
void freemost_voted_answers(Info info);

void freetop_most_active(Info info);
void freetotal_posts(Info info);
void freequestions_with_tag(Info info);
void freeget_user_info(Info info);
void freemost_voted_answers(Info info);
void freemost_answered_questions(Info info);
void freecontains_word(Info info);
void freeboth_participated(Info info);
void freebetter_answer(Info info);
void freemost_used_best_rep(Info info);
