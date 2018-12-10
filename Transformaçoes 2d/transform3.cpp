
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;

void fillVector();
void display(void);
void init(void);
void desenhaEixos();
void mouse(int button, int state, int x, int y);

int v1=0, v2=0;

vector<std::pair<float,float>> cords;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	fillVector();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	glutMouseFunc(mouse);
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
void fillVector()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cords.push_back(make_pair(-2.5 + (j), -2.5 + (i)));
		}
	}
	
}
// Mouse callback
void mouse(int button, int state, int x, int y)
{
	 v1 = (x/50);
	 v2 = (6 - (y / 50))-1;
	 cout << get<0>(cords.at(v1)) << endl;

}

void desenhaEixos()
{
	int x, y, color = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	for (x = 0; x < 8; x++) {
		if (color == 0) {
			glColor3f(0.0, 0.0, 0.0);
			color++;
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
			color = 0;
		}
		for (y = 0; y < 8; y++) {
			if (color == 0) {
				glColor3f(0.0, 0.0, 0.0);
				color++;
			}
			else {
				glColor3f(1.0, 1.0, 1.0);
				color = 0;
			}
			glBegin(GL_QUADS);
			glVertex2f(-3 + x, -3 + y);
			glVertex2f(x, -3 + y);
			glVertex2f(x, y);
			glVertex2f(-3 + x, y);

			glEnd();
		}
	}
	glColor3f(1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(get<0>(cords.at(v1)), get<0>(cords.at(v2)), 0.0);
	glutSolidSphere(.5, 50, 50);
	glPopMatrix();
	glFlush();
	
}

void display(void)
{
	// Limpar todos os pixels
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // Inicializa com matriz identidade

	desenhaEixos();

	glColor3f(1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(xtrans, ytrans, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glScalef(scale, scale, scale);
	glutWireCube(10);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();

}

void init(void)
{
	// selecionar cor de fundo (preto)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// inicializar sistema de viz.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3, 3, -3, 3, -3, 3);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
