#include "camaraEx.h"

float alfa2, beta2, raio2; // Coordenadas esféricas alfa, beta e o raio inicial.
float camX2, camY2, camZ2; // Para as cartesianas e para a câmara do GLUT.

void esfericaParaCartesiana3() {
	camX2 = raio2 * cos(beta2) * sin(alfa2);
	camY2 = raio2 * sin(beta2);
	camZ2 = raio2 * cos(beta2) * cos(alfa2);
}

void camaraExploradora() {

	alfa2 = 4.0f, beta2 = 1.0f, raio2 = 250.0f; // Coordendas esféricas alfa, beta e o raio inicial.

	esfericaParaCartesiana3();

	gluLookAt(camX2, camY2, camZ2,
		0, 0, 0,
		0.0f, 1.0f, 0.0f);

	esfericaParaCartesiana3();
}

void tecladoExplorador2(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa2 -= 0.15; break;

	case GLUT_KEY_LEFT:
		alfa2 += 0.15; break;

	case GLUT_KEY_UP:
		beta2 += 0.15f;
		// limitar o ângulo beta a 1.5 para não virar demais.
		if (beta2 > 1.5f)
			beta2 = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta2 -= 0.15f;
		// limitar o ângulo beta a 1.5 para não virar demais.
		if (beta2 < -1.5f)
			beta2 = -1.5f;
		break;

	case GLUT_KEY_F4:
		// dar o efeito de zoom diminuindo o raio da câmara.
		raio2 -= 3.0f;
		if (raio2 < 0.1f)
			raio2 = 0.1f;
		break;

	case GLUT_KEY_F1:
		// dar o efeito de zoom aumentando o raio da câmara.
		raio2 += 3.0f; break;
	}

	esfericaParaCartesiana3();
	glutPostRedisplay();
}
