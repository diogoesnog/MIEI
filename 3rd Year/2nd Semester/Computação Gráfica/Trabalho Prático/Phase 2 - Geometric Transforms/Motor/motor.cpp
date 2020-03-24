#include <stdlib.h>
#include <GL/glut.h>

#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>

#include <fstream> // Usar para ficheiro em modo C++
#include "figura.h"
#include <tinyxml.h>

using namespace std;

float alfa = 4.0f, beta = 1.0f, raio = 250.0f; // coordenadas esféricas alfa, beta e o raio inicial.
float camX, camY, camZ; // para as cartesianas e para a camara do GLUT

TiXmlNode *scene = NULL;
Figura listaFiguras = NULL;


void esfericaParaCartesiana() {
	camX = raio * cos(beta) * sin(alfa);
	camY = raio * sin(beta);
	camZ = raio * cos(beta) * cos(alfa);
}

void menu(int opcao) {
	switch (opcao) {
		case 1: glPolygonMode(GL_FRONT, GL_POINT); break;
		case 2: glPolygonMode(GL_FRONT, GL_LINE); break;
		case 3: glPolygonMode(GL_FRONT, GL_FILL); break;
	}
	glutPostRedisplay();
}

//Dado uma figura(anel ou planeta) desenha-o.
void drawFigura(Figura figura){
	// usar para as cores
	srand(time(NULL));

	// guardar os vertices da figura
	float * vertices = figura->vertices;
	int i;
	glBegin(GL_TRIANGLES);
	for(i=0;i<(figura->npontos);i+=3){
		float vermelho = (rand() % 256);
		float verde = (rand() % 256);
		float azul = (rand() % 256);
		glColor3f(vermelho/255, verde/255, azul/255);
		glVertex3f(vertices[i],vertices[i+1],vertices[i+2]);
	}
	glEnd();
}


void parsingFigura(const char* filename) {
	
	ifstream input_file(filename);
	float x, y, z, *vertices;
	int i = 0, npontos;

	input_file >> npontos;
	vertices = (float*)malloc(sizeof(float)*npontos);
	while (input_file >> x >> y >> z) {
		vertices[i++] = x;
		vertices[i++] = y;
		vertices[i++] = z;
	}
	listaFiguras = adicionaFigura(filename, vertices, npontos, listaFiguras);
	drawFigura(listaFiguras);
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
	float x, y, z, angulo;



	for (child = root->FirstChild(); child; child = child->NextSibling()) {
		tagXML = child->Value();

		if (strcmp(tagXML, "model") == 0) {
			attr = child->ToElement()->FirstAttribute();
			if (strcmp(attr->Name(), "file") == 0) {

				figura = pesquisaFigura(attr->Value(), listaFiguras);
				
				if (figura) {
					drawFigura(figura);
				}
				else {
					parsingFigura(attr->Value());
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
				if (strcmp(tagXML, "translate") == 0) {
					x = y = z = 0;
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
					glTranslatef(x, y, z);
				}
				else
					if (strcmp(tagXML, "rotate") == 0) {
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
										if (strcmp(attr->Name(), "angulo") == 0)
											angulo = atof(attr->Value());
						}
						glRotatef(angulo, x, y, z);
					}
					else
						if (strcmp(tagXML, "scale") == 0) {
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
							glScalef(x, y, z);
						}

	}
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// camara aqui inicializada com as coordenadas j� em modo cartesiano.
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	motorXML(scene);

	// End of frame
	glutSwapBuffers();
}


void processSpecialKeys(int key, int xx, int yy) {

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
			glutCreateWindow("CG-FASE2-UM");

			// Required callback registry
			glutDisplayFunc(renderScene);
			glutReshapeFunc(changeSize);

			// Callback registration for keyboard processing
			glutSpecialFunc(processSpecialKeys);

			glutCreateMenu(menu);
			glutAddMenuEntry("Ponto", 1);
			glutAddMenuEntry("Linha", 2);
			glutAddMenuEntry("Preenchido", 3);
			glutAttachMenu(GLUT_RIGHT_BUTTON);

			// OpenGL settings
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
