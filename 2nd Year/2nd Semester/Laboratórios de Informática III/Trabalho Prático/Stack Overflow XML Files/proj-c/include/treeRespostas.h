#include <stdio.h>
#include <stdlib.h>

void TreeForEachResTotalPosts(GTree* treeRes, Info info);
void TreeForEachResVotes(GTree* treeRes, Info info);
gint my_comparatorScore(gconstpointer da1, gconstpointer da2);
GTree* createScoreTree();
void TreeForEachResMostRes(GTree* treeRes, Info info);
void resetscorelist(GTree* tree);
