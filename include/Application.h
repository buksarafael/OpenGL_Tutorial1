#pragma once
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <Math3D.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <iostream>
class Application
{
public: //constructor
    Application()=default;
    Application& operator = (const Application&) = delete;

public: //methods
    bool initialize(const char* window_name,int width,int height);
    void update(const float delta_seconds);
    void render();
    void run();

private://methods
    static void key_callback(GLFWwindow*, int, int, int, int);
    static void window_resize(GLFWwindow* window,int width,int height);
public: //members
    GLFWwindow* m_Window;
    GLuint vbo;
    //add members here:
};
