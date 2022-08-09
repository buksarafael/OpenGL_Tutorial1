#pragma once
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>

class Application
{
    public:
    Application()=default;
    bool initWindow(const char* window_name,std::size_t width, std::size_t height);
    static void key_callback(GLFWwindow *window,int key,int scancode,int action, int mods);
    virtual void key_callback(Application *App, int key){}
    float getWidth() const;
    float getHeight() const;
    GLFWwindow *m_Window=nullptr;
    int m_Width=0;
    int m_Height=0;
    virtual void run();
    virtual void render()=0;
};
