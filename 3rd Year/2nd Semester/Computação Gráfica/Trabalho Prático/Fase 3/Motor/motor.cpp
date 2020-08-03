#include <tinyxml.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "figura.h"
#include "rotacao.h"
#include "catmullRom.h"
#include "escala.h"
// #include "camaraEx.h"
// #include "camaraFPS.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int camara = 1;

TiXmlNode *scene = NULL;
Figura listaFiguras = NULL;

Escala escalas = NULL, escalaAtual = NULL;
Rotacao rotacoes = NULL, rotacaoAtual = NULL;
Translacao *translacoes = NULL, *translacaoAtual = NULL;

// Tempo Atual obtido pelo GLUT para se reproduzirem as tranlações.
long tempoAtual = 0;


float alfa = 4.0f, beta = 1.0f, raio = 250.0f; // Coordendas esféricas alfa, beta e o raio inicial.
float camX, camY, camZ;

void esfericaParaCartesiana() {
	camX = raio * cos(beta) * sin(alfa);
	camY = raio * sin(beta);
	camZ = raio * cos(beta) * cos(alfa);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void motorXML(TiXmlNode* root) {

	TiXmlNode *child;
	TiXmlAttribute * attr;
	Figura figura;
	const char* tagXML;

	for (child = root->FirstChild(); child; child = child->NextSibling()) {
		tagXML = child->Value();

		if (strcmp(tagXML, "model") == 0) {
			attr = child->ToElement()->FirstAttribute();
			if (strcmp(attr->Name(), "ficheiro") == 0) {

				figura = pesquisaFigura(attr->Value(), listaFiguras);
	
				if (figura) {
					if (figura->tipoFigura == 1)
						desenhaModeloTR(figura->option.modeloTR);
					if(figura->tipoFigura == 2)
						desenhaModeloVBO(figura->option.modeloVBO);
				}
			}
		}
		else
			if (strcmp(tagXML, "group") == 0) {
				glPushMatrix();
				motorXML((child));
				glPopMatrix();
			}
			else
				if (strcmp(tagXML, "translacao") == 0)
					translacaoAtual = reproduzirTranslacao(translacaoAtual, tempoAtual);
				else
					if (strcmp(tagXML, "rotacao") == 0)
						rotacaoAtual = reproduzirRotacao(rotacaoAtual, tempoAtual);
					else
						if (strcmp(tagXML, "escala") == 0)
							escalaAtual = reproduzirEscala(escalaAtual);
	}
}

void prepara_MotorXML(TiXmlNode* root) {

	TiXmlNode* child;
	TiXmlAttribute* attr;
	Figura figura;
	const char* tagXML;
	float x, y, z, angulo, tempo;
	Ponto* listaPontos = NULL;
	int numeroPontos = -1;
	float timeTrans = -1;
	int flag;


	for (child = root->FirstChild(); child; child = child->NextSibling()) {
		tagXML = child->Value();
		if (strcmp(tagXML, "group") == 0) {
			prepara_MotorXML((child));
		}
		else
			if (strcmp(tagXML, "model") == 0) {
				attr = child->ToElement()->FirstAttribute();
				if (strcmp(attr->Name(), "ficheiro") == 0) {
					figura = pesquisaFigura(attr->Value(), listaFiguras);
					if (!figura) {

						std::regex e("(.*)(.vbo)");
						if (std::regex_match(attr->Value(), e))
							listaFiguras = parsingModeloVBO(attr->Value(), listaFiguras);
						else {
							std::regex e("(.*)(.3d)");
							if (std::regex_match(attr->Value(), e))
								listaFiguras = parsingModeloTR(attr->Value(), listaFiguras);
							else
								printf("ERRO! Ficheiro '%s' inexistente\n", attr->Value());
						}
					}
				}
			}
			else
				if (strcmp(tagXML, "translacao") == 0) {
					x = y = z = 0;
					flag = 0;
					timeTrans = 0;
					for (attr = child->ToElement()->FirstAttribute(); attr; attr = attr->Next()) {
						if (strcmp(attr->Name(), "tempo") == 0)
							timeTrans = atof(attr->Value());
						else
							if (strcmp(attr->Name(), "x") == 0) {
								x = atof(attr->Value());
								flag = 1;
							}
							else
								if (strcmp(attr->Name(), "y") == 0) {
									y = atof(attr->Value());
									flag = 1;
								}
								else
									if (strcmp(attr->Name(), "z") == 0) {
										z = atof(attr->Value());
										flag = 1;
									}
					}
					if (flag == 1)
						timeTrans = 0;
					listaPontos = NULL;
					numeroPontos = -1;
					numeroPontos = lerPontos(child, &listaPontos);
					translacoes = inserirTranslacao(listaPontos, translacoes, numeroPontos, timeTrans, x, y, z);
				}
				else
					if (strcmp(tagXML, "rotacao") == 0) {
						angulo = x = y = z = 0;
						for (attr = child->ToElement()->FirstAttribute(); attr; attr = attr->Next()) {
							if (strcmp(attr->Name(), "x") == 0)
								x = atof(attr->Value());
							else
								if (strcmp(attr->Name(), "y") == 0)
									y = atof(attr->Value());
								else
									if (strcmp(attr->Name(), "z") == 0)
										z = atof(attr->Value());
									else
										if (strcmp(attr->Name(), "tempo") == 0)
											tempo = atof(attr->Value());
										else
											if (strcmp(attr->Name(), "angulo") == 0)
												angulo = atof(attr->Value());
						}
						if (angulo)
							rotacoes = inserirRotacao(0, angulo, x, y, z, rotacoes);
						else
							rotacoes = inserirRotacao(tempo, 0, x, y, z, rotacoes);
					}
					else
						if (strcmp(tagXML, "escala") == 0) {
							x = y = z = 1;
							for (attr = child->ToElement()->FirstAttribute(); attr; attr = attr->Next()) {
								if (strcmp(attr->Name(), "x") == 0)
									x = atof(attr->Value());
								else
									if (strcmp(attr->Name(), "y") == 0)
										y = atof(attr->Value());
									else
										if (strcmp(attr->Name(), "z") == 0)
											z = atof(attr->Value());
							}
							escalas = inserirEscala(x, y, z, escalas);
						}
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// camara aqui inicializada com as coordenadas j� em modo cartesiano.
	gluLookAt(camX, camY, camZ,
		0, 0, 0,
		0.0f, 1.0f, 0.0f);
	
	/*if (camara == 1)
		camaraExploradora();
	else 
		if (camara == 2)
			camaraFPS();*/
	
	tempoAtual = glutGet(GLUT_ELAPSED_TIME);

	rotacaoAtual = rotacoes;
	translacaoAtual = translacoes;
	escalaAtual = escalas;

	motorXML(scene);

	// End of frame
	glutSwapBuffers();
}

void tecladoExplorador(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.15; break;

	case GLUT_KEY_LEFT:
		alfa += 0.15; break;

	case GLUT_KEY_UP:
		beta += 0.15f;
		// limitar o ângulo beta a 1.5 para não virar demais.
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.15f;
		// limitar o ângulo beta a 1.5 para não virar demais.
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_F4:
		// dar o efeito de zoom diminuindo o raio da câmara.
		raio -= 3.0f;
		if (raio < 0.1f)
			raio = 0.1f;
		break;

	case GLUT_KEY_F1:
		// dar o efeito de zoom aumentando o raio da câmara.
		raio += 3.0f; break;
	}

	esfericaParaCartesiana();
	glutPostRedisplay();
}


// Menu que mostra 3 opções para o preenchimento das primitivas geométricas.
void menuDireito(int opcao) {
	switch (opcao) {
	case 1: glPolygonMode(GL_FRONT, GL_POINT); break;
	case 2: glPolygonMode(GL_FRONT, GL_LINE); break;
	case 3: glPolygonMode(GL_FRONT, GL_FILL); break;
	case 4:
		glutSpecialFunc(tecladoExplorador);
		camara = 1;
		break;
	/*case 5:
		glutKeyboardFunc(tecladoFPS);
		glutSpecialFunc(tecladoExplorador2);
		camara = 2;
		break;*/
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Falta enviar o nome do ficheiro XML\n");
		return 1;
	}

	// Le o documento passado como argumento na linha de comandos.
	TiXmlDocument doc(argv[1]);
	TiXmlElement *root = NULL;

	if (doc.LoadFile()) {

		root = doc.RootElement();
		scene = root->FirstChild("scene");
		
		if (scene) {
			// Inicio do GLUT.
			glutInit(&argc, argv);
			glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
			glutInitWindowPosition(100, 100);
			glutInitWindowSize(800, 800);
			glutCreateWindow("CG-FASE3-UM");

			// Required callback registry
			glutDisplayFunc(renderScene);
			glutReshapeFunc(changeSize);
			glutIdleFunc(renderScene);

			// Callback registration for keyboard processing
			glutSpecialFunc(tecladoExplorador);

			glutCreateMenu(menuDireito);
			glutAddMenuEntry("Ponto", 1);
			glutAddMenuEntry("Linha", 2);
			glutAddMenuEntry("Preenchido", 3);
			glutAddMenuEntry("Camara Exploradora", 4);
			// glutAddMenuEntry("Camara FPS", 5);
			glutAttachMenu(GLUT_RIGHT_BUTTON);

			// OpenGL settings
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			prepara_MotorXML(scene);

			esfericaParaCartesiana();
			// enter GLUT's main cycle
			glutMainLoop();
		}
		else {
			printf("Elemento <scene> não presente no ficheiro XML.\n");
			return 1;
		}
	}
	else {
		printf("Ficheiro impossível de carregar e ler.\n");
		return 1;
	}

	return 0;
}
