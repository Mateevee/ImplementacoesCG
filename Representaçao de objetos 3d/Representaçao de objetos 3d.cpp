
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/freeglut.h>
#include <math.h>

#define NUM 60
#define PI 3.1415927

#define R 2
#define r 0.5


float current = 0;
float angle = 0;
float raio = 1.5;
float dir = 1;
bool idleOn = true;
int p = 1; 
int q = 8; 
float *vertices = NULL; 
float t = 0.0; 
int lastx = 0;
int mode = 1;

float x(int i, int j)
{
	float aux = mode==0?1:(R + r *cos((-1 + 2 * (float)j / q) * PI));
	float aux2 = cos((float)i / p * t * 2 * PI);
	return (aux*aux2);
}

float y(int i, int j)
{
	float aux = (R + r * cos((-1 + 2 * (float)j / q) * PI));
	float aux2 = mode == 0 ? 1 : sin((float)i / p * t * 2 * PI);
	return (aux * aux2);
}

float z(int i, int j)
{
	return (r * sin((-1 + 2 * (float)j / q) * PI));
}

void fillVertexArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			vertices[k++] = x(i, j);
			vertices[k++] = y(i, j);
			vertices[k++] = z(i, j);
		}
}


void display(void)
{
	int  i, j;
	vertices = new float[3 * (p + 1)*(q + 1)]; 


	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLineWidth(1.0);
	glColor3f(1,1,1);

	glRotatef(200, 1.0, 0.0, 0.0);
	glRotatef(0, 0.0, 1.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
	
	fillVertexArray();

	for (j = 0; j < q; j++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++)
		{
			glArrayElement((j + 1)*(p + 1) + i);
			glArrayElement(j*(p + 1) + i);
		}
		glEnd();
	}

	glLineWidth(4.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (j = 0; j < q; j++)
		glArrayElement((j + 1)*(p + 1) + p);
	glEnd();

	glutSwapBuffers();
}


void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);

}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'm':
		if (mode == 0)
		{
			t = 0;
			p = 1;
			mode++;
		}
		else
		{
			t = 0;
			p = 1;
			mode--;
		}
		glutPostRedisplay();
		break;
	
	case '+':
		glutPostRedisplay();
		break;

	case '-':
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
void idle()
{
	//glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	if (button == 3) // Scroll up
	{
		t += 0.01;
		p += 1;
		glutPostRedisplay();
	}
	if (button == 4)   // Scroll down
	{
		if (p > 1)
		{

			t -= 0.01;
			p -= 1;
		}
		glutPostRedisplay();
	}
}
void init(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glClearColor(0, 0, 0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	init();
	glutDisplayFunc(display);

	glutMainLoop();
}

