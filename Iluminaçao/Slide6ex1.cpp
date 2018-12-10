
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
using namespace std;

int lightEnable[3] = { 1,1,1 };
int width = 1800;
int height = 900;

float kc = 0.1f;
float kl = 0.04f;
float kq = 0.0005f;

float angle = 0;
int luz_selecionada = 0;

// Material da base
GLfloat base_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat base_difusa[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_especular[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_emissao[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat base_brilho[] = { 128.0 };

GLfloat par1[] = { 1,1,1, 1.0 };
GLfloat par2[] = { 1, 1, 1, 1.0 };
GLfloat par3[] = { 0, 0, 0.0, 1.0 };
GLfloat par4[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat par5[] = { 128.0 };

// Material do teapot
// Material do object (material branco)
GLfloat object_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat object_difusa[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat object_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat object_emissao[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat object_brilho[] = { 128.0 };

// Defini parametros da luz
GLfloat cor_luz[] = { 0.5f, 0.5f, 0.5f, 1.0 };
GLfloat cor_luz_amb[] = { 0.02, 0.02, 0.02, 0.02 };
GLfloat posicao_luz[] = { 3.0, 5.0, 5.0, 1.0 };
GLfloat cor_fonte_luz[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat cor_emissao[] = { 0.2, 0.2, 0.0, 1.0 };


GLfloat posicao_luz0[] = { 0, 7.5, 10.0, 1.0 };
GLfloat cor_luz0[] = { 1.0, 0.0, 0, 1.0 };

// Cor e posicao da luz amarela
GLfloat posicao_luz1[] = { -10.0, 7.5, -8.0, 1.0 };
GLfloat cor_luz1[] = { 0,0,1, 1.0 };

GLfloat posicao_luz2[] = { 10.0, 7.5, 8.0, 1.0 };
GLfloat cor_luz2[] = { 0, 1, 0.0, 1.0 };

GLfloat cor_luz_ativa[] = { 0.0, 0.0, 0.0, 1.0 };


GLfloat cor_luz_amb1[] = { 0.1, 0.1, 0.1, 1.0 };

GLfloat sem_cor[] = { 0.0, 0.0, 0.0, 1.0 };
int activeLight = luz_selecionada;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);               
	glEnable(GL_LIGHTING);                 
	glEnable(GL_LIGHT0);                   
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	

	glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz0);
	glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, cor_luz_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_luz1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, cor_luz1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, cor_luz_amb1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, cor_luz2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, cor_luz2);
	glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz2);

	printf("\nMenu");
	printf("\n====\n\n");
	printf("Keyboard:\n");
	printf("1,2,3 para selecionar as fontes de luz\n");
	printf("F1,F2,F3 para ativar/desativar as fontes\n");
	printf("+/- mover as fontes de luz pelo grid\n");
	printf("Pressione ESC para sair.\n");
}

void performTranslation(int n)
{
	if (luz_selecionada == 0)
	{
		if (posicao_luz0[0] +n < 10 && posicao_luz0[0]+n>-10) {
			posicao_luz0[0] += n;
		}
	}
	else if (luz_selecionada == 1)
	{
		if (posicao_luz1[2] + n < 10 && posicao_luz1[2] + n > -10) {
			posicao_luz1[2] += n;
		}
	}
	else {
		if (posicao_luz2[2] + n < 10 && posicao_luz2[2] + n>-10) {
			posicao_luz2[2] += n;
		}
	}
}

void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,
	GLfloat *brilho, GLfloat *emissao)
{
	// Define os parametros da superficie a ser iluminada
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissao);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 20, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//setMaterial(par1, par2, par3, par4, par5);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, par1);
	glMaterialfv(GL_FRONT, GL_EMISSION, par1);

	glPushMatrix();
	glColor3f(1, 1, 1);
	glLineWidth(2);
	glTranslatef(0, 2.5, 0);
	glScalef(2, 1, 2);
	glutWireCube(10);
	glPopMatrix();

	if (lightEnable[0])
	{
		glPushMatrix();
		glTranslatef(posicao_luz0[0], posicao_luz0[1], posicao_luz0[2]);
		glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0);
		if (activeLight == 0)
			glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz);
		else
			glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz0);
		glutSolidSphere(0.2, 30, 30);
		glPopMatrix();
	}

	// Define luz 1
	if (lightEnable[1])
	{
		glPushMatrix();
		glTranslatef(posicao_luz1[0], posicao_luz1[1], posicao_luz1[2]);
		glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1);
		if (activeLight == 1)
			glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz);
		else
			glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz1);
		glutSolidSphere(0.2, 30, 30);
		glMaterialfv(GL_FRONT, GL_EMISSION, sem_cor);
		glPopMatrix();
	}
	if (lightEnable[2])
	{
		glPushMatrix();
		glTranslatef(posicao_luz2[0], posicao_luz2[1], posicao_luz2[2]);
		glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz2);
		if (activeLight == 2)
			glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz);
		else
			glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz2);
		glutSolidSphere(0.2, 30, 30);
		glMaterialfv(GL_FRONT, GL_EMISSION, sem_cor);
		glPopMatrix();
	}

	glPushMatrix();
	setMaterial(object_ambient, object_difusa, object_especular, object_brilho, object_emissao);
	glRotatef(angle, 0, 1, 0);
	glutSolidTeapot(5.0);
	glPopMatrix();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-10.0f, -2.5f, -10.0);
	glVertex3f(10.0f, -2.5f, -10.0);
	glVertex3f(10.0f, -2.5f, 10.0);
	glVertex3f(-10.0f, -2.5f, 10.0);
	glEnd();

	
	glutSwapBuffers();
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

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		(lightEnable[0]) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
		lightEnable[0] = !lightEnable[0];
		break;
	case GLUT_KEY_F2:
		(lightEnable[1]) ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
		lightEnable[1] = !lightEnable[1];
		break;
	case GLUT_KEY_F3:
		(lightEnable[2]) ? glDisable(GL_LIGHT2) : glEnable(GL_LIGHT2);
		lightEnable[2] = !lightEnable[2];
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		performTranslation(1);
		break;
	case '-':
		performTranslation(-1);
		break;

	case '1':
		luz_selecionada = 0;
		break;
	case '2':
		luz_selecionada = 1;
		break;
	case '3':
		luz_selecionada = 2;
		break;
	case 'R':
		angle += 1;
		break;
	case 'r':
		angle -= 1;
		break;
	case 27:	   exit(0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
