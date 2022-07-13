#pragma once
#include <OpenGL/gl3.h>
#include <vector>
#include <iostream>
#include <VertexLayout.h>
#include <Math3D.h>
//vertex buffer.

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
public:
	void bind();
	
public:
	void create(const void* data, const VertexLayout& vertex_layout, const std::size_t vertex_count); // this function needs to bind the VAO, bind the buffer, send the data to the gpu and assign offsets with glVertexAttribPointer
private: //members
	GLuint m_Vao;
	GLuint m_Buff;
};
