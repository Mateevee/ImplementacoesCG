#version 130

uniform vec3 userColor;
out vec4 fragcolor;

in vec3 Color;

void main()
{
	fragcolor = vec4(Color,1.0);
}
