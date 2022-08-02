#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <OpenGL/gl3.h>
#include <Math3D.h>
#include <UniformHelper.h>
class ShadersProgram
{
public:
	ShadersProgram()=default;

public:
	GLuint m_ShaderProgram=0;

private:
	const char* m_VSFilePath = "/Users/rafaelb/Desktop/Tutorial1/src/shader.vs";
	const char* m_FSFilePath = "/Users/rafaelb/Desktop/Tutorial1/src/shader.fs";
	std::array<GLuint,(std::size_t)Uniform::Count>m_Uniforms;

public:
	bool create(const std::array<const char *, 2> &files);
	bool create(const char *vs,const char *fs);
	GLint getUniformPosition(Uniform uniform);
	void setUniform(Uniform,int value);
	void setUniform(Uniform,float value);
	void setUniform(Uniform,Vector2f& vec2f);
	void setUniform(Uniform,Vector3f& vec3f);
	void setUniform(Uniform,Vector4f& vec4f);
	void setUniform(Uniform,Matrix4f& mat4f);
	void bindShaders();
	void initUniforms();
};