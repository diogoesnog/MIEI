#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tags *List;

List insereTag(List tags, char *tag);
void displayListTags(List tags);

void parseTags(List tags, FILE *ficheiro, char *nome);
void fichTags(List tags, FILE *ficheiro);

void freeList(List tags);