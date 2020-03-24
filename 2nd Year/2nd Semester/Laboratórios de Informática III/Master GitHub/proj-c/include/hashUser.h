#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <libxml/parser.h>
#include <date.h>
#include <hashPost.h>

typedef struct UsersAtr {
  xmlChar* id;
  xmlChar* displayName;
  xmlChar* aboutMe; //query 5
  xmlChar* reputation;
  GTree * userPostTree;
  int nposts;
  int added;
  GSList* userOrdReputionlist;
  GSList* npostslist;

} *UsersAtr;

gint my_comparatorDatInv(gconstpointer da1, gconstpointer da2);
GHashTable* inicializaUserHashtable();
UsersAtr inicializaUsersAtr();
void adicionaUserPostlist(GHashTable* HashUsers, char* id);
void adicionaUserPosttree(GHashTable* HashUsers, char* id, PostsAtr p, Date data);
void initnUserPoststree(GHashTable* hashuser, GTree* nUserPoststree);
void TreeForEachUserInfo(GTree* userPostTree, Info info);

void destroyUserList(PostsAtr u);
void destroyPostList(PostsAtr p);
void freeUsersAtr(UsersAtr u);