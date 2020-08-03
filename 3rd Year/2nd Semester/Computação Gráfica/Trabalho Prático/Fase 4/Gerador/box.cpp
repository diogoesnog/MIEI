#include <fstream>

#include "box.h"

using namespace std;

// Função que permite gerar todos os pontos de uma box - Modo Tempo Real.

void box(float largura, float altura, float comprimento, string nomeFicheiro){

	// Abrir o ficheiro para escrita dos pontos.
	ofstream f;
	f.open(nomeFicheiro.c_str());
	
	// Primeiro triângulo da face superior 
	f<<largura/2<<" "<<-altura/2<<" "<<comprimento/2<<" ";		
	f<<largura/2<<" "<<altura/2<<" "<<comprimento/2<<" ";		
	f<<-largura/2<<" "<<altura/2<<" "<<comprimento/2<<"\n";		
		
	// Segundo triângulo da face superior 
	f<<-largura/2<<" "<<altura/2<<" "<<comprimento/2<<" ";
	f<<-largura/2<<" "<<-altura/2<<" "<<comprimento/2<<" ";		
	f<<largura/2<<" "<<-altura/2<<" "<<comprimento/2<<"\n";		

	// Primeiro triângulo da face traseira 
	f<<-largura/2<<" "<<-altura/2<<" "<<comprimento/2<<" ";
	f<<-largura/2<<" "<<altura/2<<" "<<comprimento/2<<" ";		
	f<<-largura/2<<" "<<altura/2<<" "<<-comprimento/2<<"\n";		

	// Segundo triângulo da face traseira 
	f<<-largura/2<<" "<<altura/2<<" "<<-comprimento/2<<" ";
	f<<-largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<" ";
	f<<-largura/2<<" "<<-altura/2<<" "<<comprimento/2<<"\n";		

	// Primeiro triângulo da face inferior 
	f<<-largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<" ";
	f<<-largura/2<<" "<<altura/2<<" "<<-comprimento/2<<" ";		
	f<<largura/2<<" "<<altura/2<<" "<<-comprimento/2<<"\n ";	
	
	// Segundo triângulo da face inferior 
	f<<largura/2<<" "<<altura/2<<" "<<-comprimento/2<<" ";
	f<<largura/2 <<" "<<-altura/2<<" "<<-comprimento/2<<" ";		
	f<<-largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<"\n";
	
	// Primeiro triângulo da face frontal 
	f<<largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<" ";
	f<<largura/2<<" "<<altura/2<<" "<<-comprimento/2 <<" ";		
	f<<largura/2<<" "<<altura/2<<" "<<comprimento/2<<"\n";		

	// Segundo triângulo da face frontal 
	f<<largura/2<<" "<<altura/2<<" "<<comprimento/2<<" ";
	f<<largura/2<<" "<<-altura/2<<" "<<comprimento/2<<" ";		
	f<<largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<"\n";		
	
	// Primeiro triângulo da face esquerda
	f<<-largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<" ";		
	f<<largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<" ";		
	f<<largura/2<<" "<<-altura/2<<" "<<comprimento/2<<"\n";		

	// Segundo triângulo da face esquerda
	f<<largura/2<<" "<<-altura/2<<" "<<comprimento/2<<" ";		
	f<<-largura/2<<" "<<-altura/2<<" "<<comprimento/2<<" ";		
	f<<-largura/2<<" "<<-altura/2<<" "<<-comprimento/2<<"\n";	

	// Primeiro triângulo da face direita 
	f<<-largura/2<<" "<<altura/2<<" "<<comprimento/2<<" ";
	f<<largura/2<<" "<<altura/2<<" "<<comprimento/2<<" ";		
	f<<largura/2<<" "<<altura/2<<" "<<-comprimento/2<<"\n";		

	// Segundo triângulo da face direita 
	f<<largura/2<<" "<<altura/2<<" "<<-comprimento/2<<" ";
	f<<-largura/2<<" "<<altura/2<<" "<<-comprimento/2<<" ";	
	f<<-largura/2<<" "<<altura/2<<" "<<comprimento/2<<"\n";		

	// Fechar o ficheiro.
    f.close();
}

