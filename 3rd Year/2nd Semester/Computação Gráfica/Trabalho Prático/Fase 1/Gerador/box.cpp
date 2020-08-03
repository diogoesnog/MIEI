#include "box.h"
#include <fstream>

using namespace std;

void box(float largura, float altura, float comprimento, string nomeFicheiro){

	// Manipulação do nomeFicheiro .3d
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

    f.close();
}

