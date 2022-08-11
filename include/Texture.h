#pragma once
#include <string>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
class Texture{
    public:
    Texture(const std::string& FileName);
    bool load();
    void bind(int tslot);
    void getImageSize(int &ImageWidth,int &ImageHeight){
        ImageWidth=m_imageWidth;
        ImageHeight=m_imageHeight;
    }

    const uint64_t &get_hash() const;

    private:
    std::string m_filename;
    GLenum m_textureTarget=GL_TEXTURE_2D;
    GLuint m_textureObj;
    int m_imageWidth = 0;
    int m_imageHeight=0;
    int m_imageBPP=0;

    uint64_t m_Hash=0;
    static std::hash<std::string> m_HashObj;
};