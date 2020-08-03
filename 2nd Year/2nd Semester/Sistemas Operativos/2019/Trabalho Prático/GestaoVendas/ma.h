
struct Artigo {
    int codigoArtigo;
    double precoArtigo;
};

void insereArtigo(char *nomeArtigo, double precoArtigo);
void alteraNomeArtigo(int codigoArtigo, char *nomeArtigo);
void alteraPrecoArtigo(int codigoArtigo, double precoArtigo);
void interpretaComandoMA(char *comando);