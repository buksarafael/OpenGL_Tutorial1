#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

uniform mat4 gTranslation;

out vec3 vColor;
void main()
{
    gl_Position = gTranslation*vec4(Position,1);
    vColor=Color;
}