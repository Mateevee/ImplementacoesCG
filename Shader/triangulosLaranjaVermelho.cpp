/*
  Name:        Shader Example
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Edited:	   Bruno José Dembogurski
  Update:      10/07/2018
  Last Update: 02/03/2018
  Description: Basic Shader Example. Basically Old OpenGL with Shaders
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <GL/glew.h>
//#include <glad/glad.h>
#include <GL/glut.h>
#include "glcShader.h"

void display(void);
void init (void);
void idle(void);
void keyboard(unsigned char key, int x, int y);

// Shader object
glcShader *shader = NULL;
glcShader *shader2 = NULL;
GLuint vertexbuffer;
int shaderProgram, shaderProgram2;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutCreateWindow ("Basic Shader Example");
	init ();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    printf("Pressione ESC para fechar.\n");

    glutMainLoop();

    return 0;
}

GLint getUniLoc(GLuint program, const GLchar *name)
{
    GLint loc;

    loc = glGetUniformLocation(program, name);
    if (loc == -1) printf("No such uniform named \"%s\"\n", name);
    return loc;
}

void setTriangle()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,  1.0f, 0.0f,		0.99f, 0.49f, 0.0f,
		-1.0f, -1.0f, 0.0f,		0.99f, 0.49f, 0.0f,
		 1.0f, -1.0f, 0.0f,		0.99f, 0.49f, 0.0f,

		-1.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	};
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void drawTriangle()
{
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
		sizeof(GLfloat) * 6,                  // stride
        (void*)0            // array buffer offset
    );

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(GLfloat) * 6,                  // stride
		(void*)(3 * sizeof(GLfloat))            // array buffer offset
	);

    // Draw the triangle !
	if (shader) shader->Use();
    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    // Set color variable of the fragment shader
    glUniform3f(getUniLoc(shaderProgram, "userColor"), 0.99,0.49,0.0);
	glUniform3f(getUniLoc(shaderProgram2, "userColor"), 1.0, 0.0, 0.0);

    drawTriangle();

    glutSwapBuffers ();
}

void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glewInit();
	if (glewIsSupported("GL_VERSION_2_0")) {
		printf("Ready for OpenGL 2.0\n");
	}
    else
    {
        printf("OpenGL 2.0 not supported\n");
        exit(1);
    }

    // Create shader object
    shader = new glcShader("shaders/simple.vert", "shaders/simple.frag");
	shader2 = new glcShader("shaders/simple.vert", "shaders/simple.frag");
    shaderProgram = shader->GetProgram();
	shaderProgram2 = shader2->GetProgram();

    // Set one triangle
    setTriangle();

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

void idle(void)
{
    glutPostRedisplay();
}
