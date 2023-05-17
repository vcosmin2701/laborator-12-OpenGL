/*
 *  Programul deseneaza niste dreptunghiuri care se suprapun pentru a demonstra efectul pe care il are ordinea desenarii
 *  in amestecarea culorilor in functie de alfa.
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

void myInit()
{
	glEnable(GL_BLEND); // activarea amestecarii
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // factorii sursa si destinatie
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0); // culoarea fundalului
}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// deseneaza doua dreptunghiuri care se suprapun ca un patrat stanga jos
	glColor4f(0.0, 1.0, 1.0, 0.75); // dreptunghiul rosu
	glRectf(0.0, 0.0, 0.5, 1.0);
	glFlush();

	Sleep(2000);

	glColor4f(1.0, 0.5, 0.0, 0.75); // dreptunghiul verde
	glRectf(0.0, 0.0, 1.0, 0.5);
	glFlush();

	Sleep(2000);

	// deseneaza doua patrate care se suprapun dreapta sus
	glColor4f(0.0, 1.0, 0.0, 0.75); // patratul verde
	glRectf(0.5, 0.5, 1.0, 1.0);
	glFlush();

	Sleep(2000);

	glColor4f(1.0, 0.0, 0.0, 0.75); // patratul rosu
	glRectf(0.5, 0.5, 1.0, 1.0);
	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		gluOrtho2D(0.0, 1.0, 0.0, 1.0 * (GLfloat)h / (GLfloat)w);
	}
	else {
		gluOrtho2D(0.0, 1.0 * (GLfloat)w / (GLfloat)h, 0.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Amestecarea culorilor in functie de alfa");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
