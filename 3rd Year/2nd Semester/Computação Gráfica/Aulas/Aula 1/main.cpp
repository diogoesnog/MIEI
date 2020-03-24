// Aula 1 
// Criação de um Bule que vai sempre mudando de cor e tamanho

#include <iostream>
#include <GL/glut.h>
#include <math.h>

float tamanho = 0;
float corA = 0, corB = 0, corC = 0;

// Esqueleto sempre igual para esta função.
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
    
	// Definir a câmara
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f,
		      0.0f, 0.0f, -1.0f,
			  0.0f, 1.0f, 0.0f);
    
    // Colocar as instruções de desenho
	
	// Estamos a definir as cores com o glColor
	// Estamos a criar o Bule em si com o glutWireTeapot
	// Vamos mudando sempre o tamanho em cada animação da janela
    glColor3f(cos(corA), cos(corB), cos(corC));
    glutWireTeapot(cos(tamanho)+1.2);

    //Mudar tamanho
    tamanho += 0.05;
    
    //Mudar cores
    corA += 0.005;
    corB += 0.02;
    corC += 0.01;
    
	// End of frame
    glutSwapBuffers();
}

// Esqueleto sempre igual para a main.
int main(int argc, char **argv) {
    
    // Inicializar o GLUt e a janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI");
      
    // Registo de funções para processar os eventos (Callbacks)
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	// Com o glutIdleFunc estamos a criar uma animação, invocando sempre a função renderScene
	glutIdleFunc(renderScene);

    // Algumas definições OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
    
    // Entra no ciclo processamento do GLUT
	glutMainLoop();
    
    return 0;
}

