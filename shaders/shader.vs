#version 330 core

layout (location = 0) in vec3 Position;
//layout (location = 1) in vec3 Color;
layout (location = 1) in vec2 TexCoord;

uniform mat4 gTransformation;
//out vec3 vColor;
out vec2 TexCoord0;

void main()
{
    gl_Position = gTransformation*vec4(Position,1.0);
    // vColor=Color;
    TexCoord0=TexCoord;
}