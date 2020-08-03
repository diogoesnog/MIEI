#include <fstream>

#include "plane.h"

using namespace std;

// Função que permite gerar todos os pontos de um plano - Modo Tempo Real.

void plane(float largura, float comprimento, string nomeFicheiro){

	// Plano xOz -> y=0
	float x = largura/2;
	float y = 0.0;
	float z = comprimento/2;

	// Abrir o ficheiro para escrita dos pontos.
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
	
	// Fechar o ficheiro.
	f.close();
}