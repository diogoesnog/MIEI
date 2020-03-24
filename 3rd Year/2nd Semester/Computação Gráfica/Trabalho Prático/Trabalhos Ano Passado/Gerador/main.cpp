#include <string.h>
#include <stdlib.h>

#include "esfera.h"
#include "cilindro.h"
#include "circulo.h"
#include "paralelepipedo.h"
#include "cone.h"
#include "anel.h"
#include "patch.h"

int main(int argc, char *argv[]){
	int i1,i2,i3;
	float p1,p2,p3;
	char* op=argv[1];
	FILE *f=NULL, *patch=NULL;

	if(argc<2)
		printf("ERRO!! Nenhuma 'tag' de desenho detectada!\nTem as seguintes opções:\n\t-> esfera\n\t-> circulo\n\t-> cilindro\n\t-> anel\n\t-> cone\n\t-> plano\n\t-> paralelepipedo\n\t-> patch\n");
	else
		if(strcmp(op,"esfera")==0){
			if(argc==6 || argc==7){

				if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%d",&i1)&&sscanf(argv[4],"%d",&i2)){
					f=fopen(argv[5],"w");
					if(argc==7 && strcmp(argv[6],"-vbo")==0)
						esferaVBO(p1,i1,i2,f);
					else
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
				if(argc==8 || argc==9){

					if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%f",&p3)&&sscanf(argv[5],"%d",&i1)&&sscanf(argv[6],"%d",&i2)){
						f=fopen(argv[7],"w");
						if(argc==9 && strcmp(argv[8],"-vbo")==0)
							cilindroVBO(p1,p2,p3,i1,i2,f);
						else
							cilindro(p1,p2,p3,i1,i2,f);
						fclose(f);

					}else
						printf("ERRO!! Parametros não estão correctos!\nEx: cilindro [raio] [fatias] [camadas] [altura] [aneis] [output]\n");
				}
				else
					printf("ERRO!! Número de argumentos errado\nEx: cilindro [raio] [fatias] [camadas] [altura] [aneis] [output]\n");
			}else
				if(strcmp(op,"circulo")==0){
					if(argc==7 || argc==8){

						if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%d",&i1)&&sscanf(argv[4],"%d",&i2)&&sscanf(argv[5],"%d",&i3)){
							f=fopen(argv[6],"w");
							if(argc==8 && strcmp(argv[7],"-vbo")==0)
								circuloVBO(p1,i1,i2,0,i3,f);
							else
								circulo(p1,i1,i2,0,i3,f);
							fclose(f);

						}else
							printf("ERRO!! Parametros não estão correctos\nEx: circulo [raio] [fatias] [aneis] [orientacao] [output]\n");
					}
					else
						printf("ERRO!! Número de argumentos errado\nEx: circulo [raio] [fatias] [aneis] [orientacao] [output]\n");
				}else
					if(strcmp(op,"plano")==0){
						if(argc==8 || argc==9){

							if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%d",&i1)&&sscanf(argv[5],"%d",&i2)&&sscanf(argv[6],"%d",&i3)){
								f=fopen(argv[7],"w");
								if(argc==9 && strcmp(argv[8],"-vbo")==0)
									planoVBO(p1,p2,i1,i2,0,i3,f);
								else
									plano(p1,p2,i1,i2,0,i3,f,1);
								fclose(f);

							}else
								printf("ERRO!! Parametros não estão correctos!\nEx: plano [altura] [lado] [camadas] [fatias] [orientacao] [output]\n");
						}
						else
							printf("ERRO!! Número de argumentos errado\nEx: plano [altura] [lado] [camadas] [fatias] [orientacao] [output]\n");
					}
					else
						if(strcmp(op,"paralelepipedo")==0){
							if(argc==9 || argc==10){

								if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%f",&p3)&&sscanf(argv[5],"%d",&i1)&&sscanf(argv[6],"%d",&i2)&&sscanf(argv[7],"%d",&i3)){
									f=fopen(argv[8],"w");
									if(argc==10 && strcmp(argv[9],"-vbo")==0)
										paralelepipedoVBO(p1,p2,p3,i1,i2,i3,f);
									else
										paralelepipedo(p1,p2,p3,i1,i2,i3,f);
									fclose(f);

								}else
									printf("ERRO!! Parametros não estão correctos!\nEx: paralelepipedo [lado_Y] [lado_X] [lado_Z] [camadas] [fatias_X] [fatias_Z] [output]\n");
							}
							else
								printf("ERRO!! Número de argumentos errado\nEx: paralelepipedo [lado_Y] [lado_X] [lado_Z] [camadas] [fatias_X] [fatias_Z] [output]\n");
						}
						else
							if(strcmp(op,"cone")==0){
								if(argc==8 || argc==9){

									if(sscanf(argv[2],"%f",&p1) && sscanf(argv[3],"%f",&p2) && sscanf(argv[4],"%d",&i1) && sscanf(argv[5],"%d",&i2) && sscanf(argv[6],"%d",&i3)){
										f=fopen(argv[7],"w");
										if(argc==9 && strcmp(argv[8],"-vbo")==0)
											coneVBO(p1,p2,i1,i2,i3,f);
										else
											cone(p1,p2,i1,i2,i3,f);
										fclose(f);

									}else
										printf("ERRO!! Parametros não estão correctos!\nEx: cone [raio_base] [altura] [fatias] [aneis] [camadas] [output]\n");
								}
								else
									printf("ERRO!! Número de argumentos errado\nEx: cone [raio_base] [altura] [fatias] [aneis] [camadas] [output]\n");
							}else
								if(strcmp(op,"anel")==0){
									if(argc==8 || argc==9){

										if(sscanf(argv[2],"%f",&p1) && sscanf(argv[3],"%f",&p2) && sscanf(argv[4],"%d",&i1) && sscanf(argv[5],"%d",&i2) && sscanf(argv[6],"%d",&i3)){
											f=fopen(argv[7],"w");
											if(argc==9 && strcmp(argv[8],"-vbo")==0)
												anelVBO(p1,p2,i1,i2,i3,f);
											else
												anel(p1,p2,i1,i2,i3,f);
											fclose(f);

										}else
											printf("ERRO!! Parametros não estão correctos!\nEx: anel [raio_fora] [raio_dentro] [fatias] [aneis] [orientacao] [output]\n");
									}
									else
										printf("ERRO!! Número de argumentos errado\nEx: anel [raio_fora] [raio_dentro] [fatias] [aneis] [orientacao] [output]\n");
										
								}else
									if(strcmp(op,"patch")==0){
										if(argc==5){
											if(sscanf(argv[3],"%d",&i1)){
												patch=fopen(argv[2],"r");
												if(patch){
													f=fopen(argv[4],"w");
													read_Patch(patch,f,i1);
													fclose(f);
													fclose(patch);
												}
												else
													printf("ERRO!! Ficheiro inexistente!\n");
											}
											else
												printf("ERRO!! Parametros não estão correctos!\n\nEx: patch [ficheiro] [detalhe] [output]\n");
										}
										else
											printf("ERRO!! Número de argumentos errado\nEx: patch [ficheiro] [detalhe] [output]\n");
									}
									else
										printf("ERRO!! Nenhuma 'tag' de desenho detectada!\nTem as seguintes opções:\n\t-> esfera\n\t-> circulo\n\t-> cilindro\n\t-> anel\n\t-> cone\n\t-> plano\n\t-> paralelepipedo\n\t-> patch\n");
			

}