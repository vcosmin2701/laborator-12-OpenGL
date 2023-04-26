/*
 *  Programul arata cum trebuie procedat in cazul in care ascunderea suprafetelor este rezolvata de algoritmul z-buffer si nu
 *  prin gestionarea ordinii reprezentarii obiectelor dar obiectele transparente nu ascund totusi total obiectele din spatele lor
 *  deci amestecarea este prezenta.
 */
#include "glos.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLboolean poz_viz = GL_TRUE;

// la momentul initial se priveste din fata
// la apasarea butonului stang al mouse-ului se comuta pozitia de vizualizare
void CALLBACK comuta_pozitia_vizualizare(AUX_EVENTREC* event)
{
	if (poz_viz) {
		poz_viz = GL_FALSE;
	}
	else {
		poz_viz = GL_TRUE;
	}
}

void myInit()
{
	//se fac setarile pentru iluminare 
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 0.15 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
	GLfloat mat_shininess[] = { 15.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat position[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_DEPTH_TEST);
}

void CALLBACK display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	if (poz_viz) {
		//priveste din fata
		gluLookAt(0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	else {
		//priveste din spate
		gluLookAt(0.0, 0.0, -9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	
	glPushMatrix();

	// se deseneaza sfera fiind activata ascunderea si dezactivata amestecare
	// sfera a fost dusa mai in spate
	glTranslatef(0.0, 0.0, -1.3);
	GLfloat mat_sphere_opac[] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_sphere_opac);
	auxSolidSphere(1.0);

	glPopMatrix();

	// se deseneaza cubul cu ascunderea si amestecarea activata dar cu buffer-ul z in modul read-only
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDepthMask(GL_FALSE);  // buffer-ul z in modul read-only
	GLfloat mat_cube_transp[] = { 1.0, 1.0, 0.0, 0.25 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_cube_transp);
	
	// iar cubul a fost dus mai in fata
	glTranslatef(0.0, 0.0, 1.3);	
	glRotatef(30.0, 1.0, 1.0, 1.0);
	auxSolidCube(2.0);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Transparenta si ascunderea suprafetelor");
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, comuta_pozitia_vizualizare);
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
