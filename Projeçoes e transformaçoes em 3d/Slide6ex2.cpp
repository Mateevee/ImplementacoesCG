
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
float x=0, y=0;
float xleft = 0, yleft = 0;
int   last_x, last_y;
int width = 640, height = 480;

int distOrigem = 40;
float test = 200;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHT0);                   // habilita luz 0
	glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material

	glEnable(GL_LIGHTING);                 // Habilita luz
	glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
	glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
	glEnable(GL_COLOR_MATERIAL);
}
void updateAnimation(float qnt)
{
	if (y > yleft)
	{
		yleft += qnt;
	}
	else if (y<yleft)
	{
		yleft -= qnt;
	}
	if (x > xleft)
	{
		xleft += qnt;
	}
	else if (x<xleft)
	{
		xleft -= qnt;
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//(GLfloat)width / (GLfloat)height
	gluPerspective(50, (GLfloat)width / (GLfloat)height, 1, 200.0);

	//printf("%f\n", test);
	gluLookAt(0,-80, distOrigem, 0, 0,0, 0, 1, 0);

	glColor3f(1, 1, 1);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			glLineWidth(2.0);
			glPushMatrix();
			glTranslatef(j*10,i*20, 0.0);
			glScalef(2, 4, 0);
			glutWireCube(5);
			glPopMatrix();

		}

	}
	updateAnimation(1);
	glPushMatrix();
	glScalef(1,2,.5);
	glTranslatef(xleft, yleft, 5);
	glColor3f(1, 0, 0);
	glutSolidCube(10);
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void func(int key, int cx, int cy) {
	if (key == GLUT_KEY_UP) {
		if (y < 40 )
			y += 10;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (y > 0)
			y -= 10;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (x > 0)
			x -= 10;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (x < 40)
			x += 10;
	}

}
void keyboard(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case '+':
		distOrigem--;
		if (distOrigem<20) distOrigem = 20;
		break;
	case '-':
		distOrigem++;
		if (distOrigem>180) distOrigem = 180;
		break;
	case '*':
		test+=.5;
		break;
	case '/':
		test-=.5;
		break;
	case 27:
		exit(0);
		break;
	}
}

// Motion callback
void motion(int x, int y)
{
	//rotationX += (float)(y - last_y);
	//rotationY += (float)(x - last_x);

	last_x = x;
	last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		last_x = x;
		last_y = y;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(func);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
