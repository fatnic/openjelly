#version 330 core

uniform vec3 objectColour;
uniform vec3 lightColour;

out vec4 color;

void main()
{
	color = vec4(lightColour * objectColour, 1.0f);
}
