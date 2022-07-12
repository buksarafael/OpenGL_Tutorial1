#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <OpenGL/gl3.h>
class ShadersProgram
{
public:
	ShadersProgram()=default;
	//~ShadersProgram();

public:
	bool create(const std::array<const char *, 2> &files);

	std::size_t getAttributeCount() const;

	const char* getAttributeName(const std::size_t attribute_index) const;

	std::size_t getUniformCount() const;

	const char* getUniformName(const std::size_t uniform_index) const;

	void bind(); //or glUseProgram
private:
	bool readFile(const char* pFileName,std::string& outFile);
	static void addShader(GLuint ShaderProgram,const char* pShaderText,GLenum ShaderType);
};