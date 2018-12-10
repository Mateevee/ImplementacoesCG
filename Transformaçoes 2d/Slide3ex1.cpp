
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;

void key(unsigned char key, int x, int y);
void display(void);
void init(void);
void desenhaEixos();
void func(int key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	glutKeyboardFunc(key);
	glutSpecialFunc(func);
	init();
	printf("Slide2ex1");
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}


void func(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		ytrans += 10;
	else if (key == GLUT_KEY_DOWN)
		ytrans -= 10;
	else if (key == GLUT_KEY_LEFT)
		xtrans -= 10;
	else if (key == GLUT_KEY_RIGHT)
		xtrans += 10;

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
		scale++;
		break;
	case GLUT_KEY_LEFT:
		printf("abc");
		break;
	case '-':
		scale--;
		break;
	case 'R':
		angle+=10;
		break;
	case 'r':
		angle-=10;
		break;
	}

	glutPostRedisplay();
}
void desenhaEixos()
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, -100.0);
	glVertex2f(0.0, 100.0);
	glVertex2f(-100.0, 0.0);
	glVertex2f(100.0, 0.0);
	glEnd();
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
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
