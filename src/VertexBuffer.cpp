#include <VertexBuffer.h>
#include <VertexLayout.h>

VertexBuffer::VertexBuffer(){
    glGenVertexArrays(1,&m_Vao);
    glGenBuffers(1,&m_Buff);
}
void VertexBuffer::bind(){
    glBindVertexArray(m_Vao);
}
void VertexBuffer::create(const void* data, const VertexLayout& vertex_layout, const std::size_t vertex_count){
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER,m_Buff);
    glBufferData(GL_ARRAY_BUFFER,vertex_layout.size()*vertex_count,(void *)data,GL_STATIC_DRAW);
    std::size_t offset = 0;
    int index=0;
    for(VertexAttribute v: vertex_layout.get_attributes()){
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,v.number_of_floats,GL_FLOAT,GL_FALSE,vertex_layout.size(),(void *)offset);
        offset +=v.number_of_floats*sizeof(float);
        index++;
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    for(int i =0;i<index;i++)
        glDisableVertexAttribArray(i);
}
VertexBuffer::~VertexBuffer(){
    glDeleteVertexArrays(1,&m_Vao);
    glDeleteBuffers(1,&m_Buff);
}