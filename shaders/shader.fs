#version 330 core

uniform sampler2D gSampler;

out vec4 FragColor;
//in vec3 vColor;
in vec2 TexCoord0;

void main()
{    FragColor=texture(gSampler,TexCoord0);
}