#version 330 core

in vec3 ourColour;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, TexCoords) * vec4(ourColour, 1.0f);
}
