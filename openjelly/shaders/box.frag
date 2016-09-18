#version 330 core

in vec3 TexCoords;
out vec4 color;

uniform samplerCube texture01;

void main()
{
	color = texture(texture01, TexCoords);
}
