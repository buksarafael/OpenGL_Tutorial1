#version 330 core

uniform sampler2D gSampler;

out vec4 FragColor;
//in vec3 vColor;
in vec2 TexCoord0;

void main()
{
    //FragColor = vec4(TexCoord0.xy,0.0,0.0);
    FragColor=texture(gSampler,TexCoord0);
}