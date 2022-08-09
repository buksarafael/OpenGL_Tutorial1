#version 330 core

in vec3 Position;
//in vec3 Color;
in vec2 TexCoord;

uniform mat4 gTransformation;
//out vec3 vColor;
out vec2 TexCoord0;

void main()
{
    gl_Position = gTransformation*vec4(Position,1.0);
    // vColor=Color;
    TexCoord0=TexCoord;
}