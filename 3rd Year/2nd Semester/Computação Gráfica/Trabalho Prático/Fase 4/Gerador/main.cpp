#include <stdlib.h>

#include "plane.h"
#include "box.h"
#include "sphere.h"
#include "cone.h"
#include "anel.h"

using namespace std;

int main(int argc, char **argv) {
	
	// O nome do objeto é logo o nosso primeiro argumento.
	std::string objeto(argv[1]);

	// Verificar qual a figura que se pretende gerar.
	// Invocar a função adequada à figura que se pediu.

	if (!objeto.compare("box")) {
		if (argc == 6)
			// void box(float largura, float altura, float comprimento, string nomeFicheiro)
			box(atof(argv[2]), atof(argv[3]), atof(argv[4]), argv[5]);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("plane")) {
		if (argc == 5)
			// void plane(float largura, float comprimento, string nomeFicheiro)
			plane(atof(argv[2]), atof(argv[3]), argv[4]);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("sphere")) {
		if (argc == 6)
			// void sphere(float raio, int fatias, int camadas, string nomeFicheiro)
			sphere(atof(argv[2]), atof(argv[3]), atof(argv[4]), argv[5]);
		if (argc == 7 && strcmp(argv[2], "-vbo") == 0)
			sphereVBO(atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("cone")) {
		if (argc == 7)
			// void cone(float raio, float altura, int fatias, int camadas, string nomeFicheiro)
			cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
		else printf("Argumentos em falta.\n");
	}
	else if (!objeto.compare("anel")) {
		if (argc == 7)
			// void anel(float raioFora, float raioDentro, int fatias, int aneis, string nomeFicheiro)
			anel(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
		else printf("Argumentos em falta.\n");
	}

	else printf("O objeto impossivel de reconhecer pelo gerador.\n");

	return 0;
}