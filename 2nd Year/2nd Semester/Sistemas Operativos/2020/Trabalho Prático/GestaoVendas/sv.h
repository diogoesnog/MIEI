
struct ArtigoStock {
    int codigoArtigo;
    int quantArtigo;
};

struct Venda {
    int codigoArtigo;
    int quantArtigo;
    double montanteTotal;
};

typedef struct comando {
    int codigoArtigo;
    int quantidadeArtigo;
} Comando;

int existeArtigo(int codigoArtigo);
void insereNovaVenda(int codigoArtigo, int quantArtigo, int novaQuantArtigo);
void verificaStockPreco(int codigoArtigo);
void alteraQuantArtigo(int codigoArtigo, int quantArtigo);
void geraAgregacao();