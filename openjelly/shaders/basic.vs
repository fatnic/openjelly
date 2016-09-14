#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 texCoords;

out vec3 ourColour;
out vec2 TexCoords;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
    ourColour = colour;
    TexCoords = vec2(texCoords.x, 1.0 - texCoords.y);
}
