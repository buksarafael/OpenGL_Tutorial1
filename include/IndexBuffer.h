#pragma once
#include <OpenGL/gl3.h>
#include <VertexBuffer.h>
#include <iostream>

class IndexBuffer{
    public:
    IndexBuffer();
    ~IndexBuffer();

    public:
    void bind();
    void create(const VertexBuffer &vertex_buffer,const uint32_t *data,const std::size_t size);
    std::size_t getSize();

    private:
    GLuint m_IBO;
    std::size_t m_Size=0;
};