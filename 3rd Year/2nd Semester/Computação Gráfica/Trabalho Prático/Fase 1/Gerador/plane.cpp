#include "plane.h"
#include <fstream>

using namespace std;

void plane(float largura, float comprimento, string nomeFicheiro){

	// Plano xOz -> y=0
	float x = largura/2;
	float y = 0.0;
	float z = comprimento/2;

	// Manipulação do ficheiro .3d
	ofstream f;
	f.open(nomeFicheiro.c_str());

	// Primeiro triângulo
	f<<x<<" "<<y<<" "<<z<<" ";
	f<<x<<" "<<y<<" "<<-z<<" ";
	f<<-x<<" "<<y<<" "<<z<<"\n";

	// Segundo triângulo
	f<<x<<" "<<y<<" "<<-z<<" ";
	f<<-x<<" "<<y<<" "<<-z<<" ";
	f<<-x<<" "<<y<<" "<<z<<"\n";

	f.close();
}