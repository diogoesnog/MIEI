// Definir Fator de Balanceamento

// A Esquerda pode ser maior
// A Direita pode ser maior
// Podem ter ambas a mesma altura
typedef enum fatorBalanceamento { 
    ESQUERDA,
    DIREITA,
    IGUAIS 
} FB;

typedef struct AVLTree {
    FB fatorBalanceamento;
    int valorNodo;
    struct AVLTree *direita;
    struct AVLTree *esquerda;
} AVLTree;

AVLTree inserirÁrvore(AVLTree *arvore, int elemento, int *cresceu);
int nonAVL_treeHeight(AVLTree *arvore);
int treeHeight(AVLTree *arvore);
int isAVL (AVLTree *arvore);
int isAVL_opt (AVLTree *arvore);