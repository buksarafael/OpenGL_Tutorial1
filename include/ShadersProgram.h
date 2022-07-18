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
	GLint getUniformPosition(Uniform);
	void setUniform(Uniform,int);
	void setUniform(Uniform,float);
	void setUniform(Uniform,Vector2f&);
	void bindShaders();


private:
	//static void addShader(GLuint ShaderProgram,const char* pShaderText,GLenum ShaderType);
	void initUniforms();
};