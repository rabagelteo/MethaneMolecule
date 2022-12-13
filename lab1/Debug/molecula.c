#include "glos.h"

#include <gl.h>
#include <glu.h>
#include <glaux.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);

void CALLBACK rot_z_up(AUX_EVENTREC* event);
void CALLBACK rot_z_down(AUX_EVENTREC* event);
void CALLBACK Animatie(void);



static GLfloat x = 0, y = 0, alfa = 0, z = 0;
GLUquadricObj* qobj;
GLUnurbsObj* theNurb; // initiala

void myinit(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK rot_z_up(AUX_EVENTREC* event)
{
	alfa = alfa + 10;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event)
{
	alfa = alfa - 10;
}

void CALLBACK Animatie(void) {
	alfa -= 0.2;
	display();
	Sleep(6);
}

void CALLBACK display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	qobj = gluNewQuadric();

	// O LINIE		
	glBegin(GL_LINES);
	glVertex2f(-1000,0);
	glVertex2f(1000,0);
	glEnd();

	// O LINIE		
	glBegin(GL_LINES);
	glVertex2f(0, 1000);
	glVertex2f(0, -1000);
	glEnd();

	// 5 sfere si un cilindru 
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(-3,5,7);
	glColor3f(0, 1, 1);
	gluSphere(qobj, 20, 30, 30);
	glPopMatrix();

	auxSwapBuffers();
}


void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w,
			-160.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
	else
		glOrtho(-160.0 * (GLfloat)w / (GLfloat)h,
			160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB);
	auxInitPosition(0, 0, 1000, 800);
	auxInitWindow("Molecula de metan");
	myinit();

	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
	auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);

	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return(0);
}