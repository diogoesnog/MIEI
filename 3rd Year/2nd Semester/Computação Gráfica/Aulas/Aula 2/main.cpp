// Aula 2

#include <GL/glut.h>
#include <math.h>

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

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here

// put drawing instructions here

	// Eixo x verde
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(-20.0f, 0.0f, 0.0f);
	glVertex3f(20.0f, 0.0f, 0.0f);
	glEnd();

	// Eixo y azul
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -20.0f, 0.0f);
	glVertex3f(0.0f, 20.0f, 0.0f);
	glEnd();

	// Eixo z vermelho
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -20.0f);	
	glVertex3f(0.0f, 0.0f, 20.0f);
	glEnd();

	// Base
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	// Triangulo esquerda
	glColor3f(1, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 1.0f, 0.5f);
	glEnd();

	// Triangulo direita
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 1.0f, 0.5f);
	glEnd();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events



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

	
// put here the registration of the keyboard callbacks



//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
