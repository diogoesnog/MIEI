// Estrutura que guarda a Closing Tag (concatenada com os espaços) e o número de espaços
typedef struct tags
{
    char *closingTag;
    int numberSpaces;
    struct tags *next;

} Tags;

// Função de Inicialização da Lista Ligada.
Tags *init();

// Função de Inserção na Lista Ligada.
Tags *insertTag(Tags *listTags, char *nameTag, int numberSpaces);

// Funções para remover da Lista Ligada.
Tags *removeFirstTag(Tags *listTags);
Tags *removeClosedTags(Tags *listTags, int numberSpaces);

// Função para devolver a Opening Tag com as devidas Closed Tags.
char *newInitialTag(Tags *listTags, char *initialTag, int numberSpaces);

// Função usadas para imprimir os valores da Lista Ligada.
void printFinalClosingTags(Tags *listTags);
void printTags(Tags *listTags);