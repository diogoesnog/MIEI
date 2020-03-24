#include <stdlib.h>
#include <GL/glut.h>

#include <stdio.h>

#include <vector>
#include <string>

#include <fstream> // file stream

#include <tinyxml.h>

using namespace std;

float alfa = 4.0f, beta = 1.0f, raio = 2.0f; // coordenadas esféricas alfa, beta e o raio inicial.
float camX, camY, camZ; // para as cartesianas e para a câmara do GLUT

// vetor que fica com o nome dos ficheiros a demonstrar.
vector<string> ficheiros;


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



void drawScene() {
	float x, y, z;

	// iterador para mexer no vetor dos ficheiros
	vector<string>::const_iterator figura;

	for (figura = ficheiros.begin(); figura != ficheiros.end(); ++figura) {

		glBegin(GL_TRIANGLES);

		if (*figura == "box.3d") {
			ifstream input_file("box.3d");
			while (input_file >> x >> y >> z) {
				glColor3f(1, 1, 1);
				glVertex3f(x, y, z);
			}
		}
		else if (*figura == "cone.3d") {
			ifstream input_file("cone.3d");
			while (input_file >> x >> y >> z) {
				glColor3f(1, 1, 1);
				glVertex3f(x, y, z);
			}
		}
		else if (*figura == "plane.3d") {
			ifstream input_file("plane.3d");
			while (input_file >> x >> y >> z) {
				glColor3f(1, 1, 1);
				glVertex3f(x, y, z);
			}
		}
		else if (*figura == "sphere.3d") {
			ifstream input_file("sphere.3d");
			while (input_file >> x >> y >> z) {
				glColor3f(1, 1, 1);
				glVertex3f(x, y, z);
			}
		}

		glEnd();
	}
}



void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// câmara aqui inicializada com as coordenadas já em modo cartesiano.
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	drawScene();

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
		raio -= 0.15f;
		if (raio < 0.1f)
			raio = 0.1f;
		break;

	case GLUT_KEY_F1:
		// dar o efeito de zoom aumentando o raio da câmara.
		raio += 0.15f; break;
	}
	
	esfericaParaCartesiana();
	
	glutPostRedisplay();

}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Falta enviar o nome do ficheiro XML\n");
		return 1;
	}

	// Lê o documento passado como argumento na linha de comandos.
	TiXmlDocument doc(argv[1]);
	if (doc.LoadFile()) {
		const char* file;
		TiXmlElement *scene = doc.FirstChildElement("scene");
		if (scene) {
			TiXmlElement *linha = scene->FirstChildElement("model")->ToElement();

			for (linha; linha != NULL; linha = linha->NextSiblingElement()) {
				file = linha->Attribute("file");
				if (file != NULL) {
					// colocar no vetor ficheiros o nome do ficheiro.3d lido no xml. 
					ficheiros.push_back(file);
				}
			}
		}
		else {
			printf("Elemento <scene> não presente no ficheiro XML.\n");
		}
	}
	else {
		printf("Ficheiro impossível de carregar e ler.\n");
	}

	// Início do GLUT.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG-FASE1-UM");

	// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutSpecialFunc(processSpecialKeys);

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Passar de coordenadas esféricas para cartesianas.
	esfericaParaCartesiana();

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}