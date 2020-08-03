#include "camaraFPS.h"

float x2 = 0, y2 = 2, z2 = 5;

float a = M_PI, b = -0.2, r;

float camXX, camYY, camZZ; // Para as cartesianas e para a câmara do GLUT.

void esfericaParaCartesiana1() {
	camXX = r * cos(b) * sin(a);
	camYY = r * sin(b);
	camZZ = r * cos(b) * cos(a);
}

void camaraFPS() {
	x2 = 0, y2 = 2, z2 = 5;
	a = M_PI, b = -0.2;

	esfericaParaCartesiana1();

	gluLookAt(x2, y2, z2,
		camXX, camYY, camZZ, 0.0f, 1.0f, 0.0f);

	esfericaParaCartesiana1();
}

void tecladoFPS(unsigned char key, int xx, int yy) {
	switch (key) {
	case 'd':
		x2 += 0.7 * sin(M_PI_2 - M_PI_2);
		z2 += 0.7 * cos(M_PI_2 - M_PI_2);
		break;
	case 'a':
		x2 += 0.7 * sin(M_PI_2 + M_PI_2);
		z2 += 0.7 * cos(M_PI_2 + M_PI_2);
		break;
	case 'w':
		x2 += 0.7 * sin(M_PI_2);
		z2 += 0.7 * cos(M_PI_2);
		break;
	case 's':
		x2 -= 0.7 * sin(M_PI_2);
		z2 -= 0.7 * cos(M_PI_2);
		break;
	}
	esfericaParaCartesiana1();
	glutPostRedisplay();
}
