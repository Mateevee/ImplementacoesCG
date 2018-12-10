
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <vector>
using namespace std;

int width = 1000;
int height = 500;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
float vx=2, vy=0;
float gravity = 0.5;
float bounce = .7;
vector<std::pair<float, float>> cords;
void idle()
{
	float x;
	float y;



		get<0>(cords.at(0)) += vx;
		get<1>(cords.at(0)) += vy;

		x = get<0>(cords.at(0));
		y = get<1>(cords.at(0));

		if (x - 20 > width || x + 20 < 0) {
			vx *= -1;
		}
		vy -= gravity;

		if (x + 20 > width || x - 20 < 0) {
			vx *= -1;
		}

		if (y + 20 < 0) {// ||

												 
			get<1>(cords.at(0)) = 0;
			vy *= -bounce;
			if (vy>0 && vy< 2.0)
				vy = 0;
			if (abs(vx) < 1.1)
				vx = 0;
		}
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(1,1,1, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer,
	cords.push_back(make_pair(80 ,450));
}

void display(void)
{
	float sphereSize = 30.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, -sphereSize, sphereSize);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 0, 0);
	glTranslatef(get<0>(cords.at(0)), get<1>(cords.at(0)), 0.0); 
	glutSolidSphere(20.0, 100, 100);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void keyboard(unsigned char key, int x, int y)
{
	if (tolower(key) == 27) exit(0);
	if (tolower(key) == 'u') vy += 1;
}

// Motion callback
void motion(int x, int y)
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Animation Base");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
