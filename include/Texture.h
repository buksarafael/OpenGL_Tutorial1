#pragma once
#include <string>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
class Texture{
    public:
    Texture(GLenum TextureTarget,const std::string& FileName);
    bool load();
    void bind(GLenum TextureUnit);
    private:
    std::string m_filename;
    GLenum m_textureTarget;
    GLuint m_textureObj;
};