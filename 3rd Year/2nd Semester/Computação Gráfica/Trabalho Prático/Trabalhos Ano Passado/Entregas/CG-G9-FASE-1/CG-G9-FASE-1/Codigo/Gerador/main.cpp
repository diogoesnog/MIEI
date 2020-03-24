#include <string.h>
#include <stdlib.h>

#include "esfera.h"
#include "cilindro.h"
#include "paralelepipedo.h"
#include "cone.h"

int main(int argc, char *argv[]){
	int i1,i2,i3;
	float p1,p2,p3;
	char* op=argv[1];
	FILE* f=NULL;

	if(argc<2)
		printf("ERRO!! Nenhuma 'tag' de desenho detectada!\nTem as seguintes opções:\n\t-> esfera\n\t-> circulo\n\t-> cilindro\n\t-> cone\n\t-> plano\n\t-> paralelepipedo\n");
	else
		if(strcmp(op,"esfera")==0){
			if(argc==6){

				if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%d",&i1)&&sscanf(argv[4],"%d",&i2)){
					f=fopen(argv[5],"w");
					esfera(p1,i1,i2,f);
					fclose(f);

				}else
					printf("ERRO!! Parametros não estão correctos!\nEx: esfera [raio] [camadas] [fatias] [output]\n");
			}
			else
				printf("ERRO!! Número de argumentos errado\nEx: esfera [raio] [camadas] [fatias] [output]\n");
		}
		else
			if(strcmp(op,"cilindro")==0){
				if(argc==8){

					if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%f",&p3)&&sscanf(argv[5],"%d",&i1)&&sscanf(argv[6],"%d",&i2)){
						f=fopen(argv[7],"w");
						cilindro(p1,p2,p3,i1,i2,f);
						fclose(f);

					}else
						printf("ERRO!! Parametros não estão correctos!\nEx: cilindro [raio] [fatias] [camadas] [altura] [aneis] [output]\n");
				}
				else
					printf("ERRO!! Número de argumentos errado\nEx: cilindro [raio] [fatias] [camadas] [altura] [aneis] [output]\n");
			}else
				if(strcmp(op,"circulo")==0){
					if(argc==7){

						if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%d",&i1)&&sscanf(argv[4],"%d",&i2)&&sscanf(argv[5],"%d",&i3)){
							f=fopen(argv[6],"w");
							circulo(p1,i1,i2,0,i3,f);
							fclose(f);

						}else
							printf("ERRO!! Parametros não estão correctos\nEx: circulo [raio] [fatias] [aneis] [orientacao] [output]\n");
					}
					else
						printf("ERRO!! Número de argumentos errado\nEx: circulo [raio] [fatias] [aneis] [orientacao] [output]\n");
				}else
					if(strcmp(op,"plano")==0){
						if(argc==8){

							if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%d",&i1)&&sscanf(argv[5],"%d",&i2)&&sscanf(argv[6],"%d",&i3)){
								f=fopen(argv[7],"w");
								plano(p1,p2,i1,i2,0,i3,f);
								fclose(f);

							}else
								printf("ERRO!! Parametros não estão correctos!\nEx: plano [altura] [lado] [camadas] [fatias] [orientacao] [output]\n");
						}
						else
							printf("ERRO!! Número de argumentos errado\nEx: plano [altura] [lado] [camadas] [fatias] [orientacao] [output]\n");
					}
					else
						if(strcmp(op,"paralelepipedo")==0){
							if(argc==8){

								if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%f",&p3)&&sscanf(argv[5],"%d",&i1)&&sscanf(argv[6],"%d",&i2)){
									f=fopen(argv[7],"w");
									paralelepipedo(p1,p2,p3,i1,i2,f);
									fclose(f);

								}else
									printf("ERRO!! Parametros não estão correctos!\nEx: paralelepipedo [altura] [lado_X] [lado_Z] [camadas] [fatias] [output]\n");
							}
							else
								printf("ERRO!! Número de argumentos errado\nEx: paralelepipedo [altura] [lado_X] [lado_Z] [camadas] [fatias] [output]\n");
						}
						else
							if(strcmp(op,"cone")==0){
								if(argc==8){

									if(sscanf(argv[2],"%f",&p1) && sscanf(argv[3],"%f",&p2) && sscanf(argv[4],"%d",&i1) && sscanf(argv[5],"%d",&i2) && sscanf(argv[6],"%d",&i3)){
										f=fopen(argv[7],"w");
										cone(p1,p2,i1,i2,i3,f);
										fclose(f);

									}else
										printf("ERRO!! Parametros não estão correctos!\nEx: cone [raio_base] [altura] [fatias] [aneis] [camadas] [output]\n");
								}
								else
									printf("ERRO!! Número de argumentos errado\nEx: cone [raio_base] [altura] [fatias] [aneis] [camadas] [output]\n");
							}else
								printf("ERRO!! Nenhuma 'tag' de desenho detectada!\nTem as seguintes opções:\n\t-> esfera\n\t-> circulo\n\t-> cilindro\n\t-> cone\n\t-> plano\n\t-> paralelepipedo\n");
			

}