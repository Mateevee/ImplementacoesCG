#version 130

attribute vec3 pos;
attribute vec3 color;

out vec3 Color;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	Color = color;
}
