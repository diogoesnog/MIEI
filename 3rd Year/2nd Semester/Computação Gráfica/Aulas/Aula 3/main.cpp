#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float raio = 5;
float camHorizontal = 0;
float camVertical = 0;

float camHorizontalX = 0;
float camHorizontaY = 0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCylinder(float radius, float height, int slices) {

	int fatias = slices;

	// M_PI é o valor de PI
	float angulo = (2 * M_PI) / fatias;
	float ladoAuxiliar1, ladoAuxiliar2 = 0;

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < fatias; i++) {

		ladoAuxiliar1 = ladoAuxiliar2;
		ladoAuxiliar2 += angulo;

		//Base Superior
		glColor3f(0, 1, 0);
		glVertex3f(0, height, 0);
		glVertex3f(sin(ladoAuxiliar1), height, cos(ladoAuxiliar1));
		glVertex3f(sin(ladoAuxiliar2), height, cos(ladoAuxiliar2));

		//Base Inferior
		glVertex3f(0, 0, 0);
		glVertex3f(sin(ladoAuxiliar2), 0, cos(ladoAuxiliar2));
		glVertex3f(sin(ladoAuxiliar1), 0, cos(ladoAuxiliar1));

		//Dois triângulos para os lados
		glColor3f(1, 1, 0);
		glVertex3f(sin(ladoAuxiliar1), height, cos(ladoAuxiliar1));
		glVertex3f(sin(ladoAuxiliar1), 0, cos(ladoAuxiliar1));
		glVertex3f(sin(ladoAuxiliar2), 0, cos(ladoAuxiliar2));

		glColor3f(1, 0.5, 0);
		glVertex3f(sin(ladoAuxiliar1), height, cos(ladoAuxiliar1));
		glVertex3f(sin(ladoAuxiliar2), 0, cos(ladoAuxiliar2));
		glVertex3f(sin(ladoAuxiliar2), height, cos(ladoAuxiliar2));
	}
	glEnd();
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(raio*sin(camHorizontal + camHorizontalX)*cos(camVertical + camHorizontaY), raio*sin(camVertical + camHorizontaY), raio*cos(camHorizontal + camHorizontalX)*cos(camVertical + camHorizontaY),
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	drawCylinder(1,2,10);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char tecla, int xx, int yy) {

	switch (tecla) {
	case 'a':
		raio -= 0.1;
		break;
	case 'd':
		raio += 0.1;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int tecla, int xx, int yy) {

	switch (tecla) {
	case GLUT_KEY_UP:
		if (camVertical + 0.05 < M_PI_2)   //Para câmera não virar ao contrário
			camVertical += 0.05;
		break;
	case GLUT_KEY_DOWN:
		if (camVertical - 0.05 > -M_PI_2)  //Para câmera não virar ao contrário
			camVertical -= 0.05;
		break;

	case GLUT_KEY_LEFT:
		camHorizontal -= 0.05;
		break;
	case GLUT_KEY_RIGHT:
		camHorizontal += 0.05;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
