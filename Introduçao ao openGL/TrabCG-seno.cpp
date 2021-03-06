
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"

void display(void);
void init(void);
void key(unsigned char key, int x, int y);
void resize(int width, int height);
int tam[] = { 6,12,180 };
int tamHelper = 0;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutReshapeFunc(resize);

	glutCreateWindow("Seno");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	printf("Pressione ESC para fechar.\n");
	glutMainLoop();

	return 0;
}
double rad(int x)
{
	return (x * 3.14159265359) / 180;
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
	printf("Slices selecionadas: %d\n", tam[tamHelper]);
	int seg = tam[tamHelper];
	int num = 360 / seg;
	int p = 400 / seg;
	for (int i = 0; i <= seg; i++)
	{
		glVertex3d(p*i, sin(rad(num*i)), 0.0);

	}
	glEnd();
	glutSwapBuffers();
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);              
	glLoadIdentity();
	glOrtho(-10.0, 390, -2, 2, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
}
static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':	
		exit(0);
		break;

	case '+':
		if (tamHelper == 2)
		{
			tamHelper = 0;

		}
		else
		{	
			tamHelper++;
		}
		break;

	case '-':
		if (tamHelper == 0)
		{
			tamHelper = 2;

		}
		else
		{
			tamHelper++;
		}
		tamHelper--;
		break;
	}

	glutPostRedisplay();
}
