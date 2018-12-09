
#include <iostream>
#include <GL/glut.h>
#include <vector>
//#include <glcFPSViewer.h>
using namespace std;

float desiredFPS = 60;
float var = 0.0f;
float dir = 1.0f;
//glcFPSViewer *fpsViewer = new glcFPSViewer((char*) "Triangle Animation. ", (char*) " - Press ESC to Exit");

void display(void);
void init(void);
void idle();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void fillVector();

vector<std::pair<float, float>> cords;
vector<std::pair<int, int>> ori;

void fillVector()
{
	for (int  i = 0; i < 6; i++)
	{
		ori.push_back(make_pair(1,1));
	}
	cords.push_back(make_pair(.3, .2));
	cords.push_back(make_pair(0.5, .8));
	cords.push_back(make_pair(.8, .3));

	cords.push_back(make_pair(.1, .7));
	cords.push_back(make_pair(0.9, .2));
	cords.push_back(make_pair(.3, .8));
}

void idle()
{
	float t, desiredFrameTime, frameTime;
	static float tLast = 0.0;

	t = glutGet(GLUT_ELAPSED_TIME);
	t /= 1000.0;

	frameTime = t - tLast;
	desiredFrameTime = 1.0 / (float)(desiredFPS);

	if (frameTime <= desiredFrameTime)
		return;


	float x;
	float y;
	for (int i = 0; i < 6; i++)
	{
		x = get<0>(cords.at(i));
		y = get<1>(cords.at(i));

		if (x <= -0.001 || x >= 1.0) get<0>(ori.at(i)) *= -1;
		get<0>(cords.at(i)) += get<0>(ori.at(i)) * 0.005;

		if (y<= -0.001 || y >= 1.0) get<1>(ori.at(i)) *= -1;
		get<1>(cords.at(i)) += get<1>(ori.at(i)) * 0.005;

	}
	
	tLast = t;

	glutPostRedisplay();

}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void display(void)
{
	// Limpar todos os pixels
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 6; i++)
	{
		if(i>2)
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(get<0>(cords.at(i)), get<1>(cords.at(i)));
	}
	glPopMatrix();
	glEnd();
	glutSwapBuffers();

	// Print FPS
	//fpsViewer->drawFPS();
}

void init(void)
{
	// selecionar cor de fundo (preto)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// inicializar sistema de viz.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		desiredFPS = 60;
		break;
	case '2':
		desiredFPS = 30;
		break;
	case '3':
		desiredFPS = 10;
		break;
	case 27:
		exit(0);
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	fillVector();
	cout << "Triangle Animation Example" << endl;
	cout << "--------------------------" << endl;
	cout << "Press 1 to change FPS to ~60" << endl;
	cout << "Press 2 to change FPS to ~30" << endl;
	cout << "Press 3 to change FPS to ~10" << endl;
	cout << "Press ESC to exit" << endl;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("");
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	init();
	glutDisplayFunc(display);
	glutFullScreen();
	glutMainLoop();

	return 0;
}
