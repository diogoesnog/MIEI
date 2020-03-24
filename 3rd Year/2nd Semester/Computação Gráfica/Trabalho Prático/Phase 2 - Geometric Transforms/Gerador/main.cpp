#include <stdlib.h>

#include "plane.h"
#include "box.h"
#include "sphere.h"
#include "cone.h"
#include "anel.h"

using namespace std;

int main(int argc, char **argv) {
	
	std::string extensao(".3d");
	std::string objeto(argv[1]);

	// Cria-se o nome de todo o ficheiro .3d que corresponde à string passada como argumento mais a extensao .3d
	// Ex: sphere.3d 
	std::string ficheiro = objeto + extensao;

	// Verifica qual a figura que foi passada como argumento
	// Depois de verificar, invoca a função apropriada
	if (!objeto.compare("box")) {
		if (argc == 6)
			// void box(float largura, float altura, float comprimento, string nomeFicheiro)
			box(atof(argv[2]), atof(argv[3]), atof(argv[4]), ficheiro);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("plane")) {
		if (argc == 5)
			// void plane(float largura, float comprimento, string nomeFicheiro)
			plane(atof(argv[2]), atof(argv[3]), ficheiro);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("sphere")) {
		if (argc == 6)
			// void sphere(float raio, int fatias, int camadas, string nomeFicheiro)
			sphere(atof(argv[2]), atof(argv[3]), atof(argv[4]), argv[5]);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("cone")) {
		if (argc == 7)
			// void cone(float raio, float altura, int fatias, int camadas, string nomeFicheiro)
			cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), ficheiro);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("anel")) {
		if (argc == 6) {
			// void anel(float raio_fora, float raio_dentro,int fatias, int aneis,  string nomeFicheiro)
			anel(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]),ficheiro);
		}
		else printf("Argumentos em falta.\n");
	}

	else printf("O objeto impossivel de reconhecer pelo gerador.\n");

	return 0;
}