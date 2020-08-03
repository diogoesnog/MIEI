// Defines para controlar se é uma Opening Tag ou Closing Tag.
#define isOpening 1
#define isClosing 0

// Defines para controlar os vários Tipos de Tag existentes.
#define defaultTag 2
#define attributeTag 3
#define selfClosingTag 4

// Função que verifica se estamos perante uma Tag Automatically Self Closing.
int isAutoSelfClosing(char *text);
// Função que conta o número de espaços que da Tag fazem parte.
int countInitialSpaces(char *text);
// Função que trata de escrever as Opening e Closing Tags já com os devidos espaços iniciais.
char *tagWithSpaces(char *text, int initialOrFinal, int isAtributte, int numberSpaces);