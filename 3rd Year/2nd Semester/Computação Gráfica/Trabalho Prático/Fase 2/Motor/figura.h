using namespace std;


typedef struct figura {
	const char *nome;
	float* vertices;
	int npontos;
	struct figura *next;
}*Figura, Lista;

Figura adicionaFigura(const char *nome, float *vertices, int npontos, Figura l);
Figura pesquisaFigura(const char *nome, Figura l);