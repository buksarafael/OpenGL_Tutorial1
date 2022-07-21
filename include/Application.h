#pragma once
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <Math3D.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <ShadersProgram.h>
#include <iostream>
#include <array>
#include <Pipeline.h>
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
    void initVertex();
    void initShaders();
    void initAll();

private://methods
    static void key_callback(GLFWwindow*, int, int, int, int);
    static void window_resize(GLFWwindow* window,int width,int height);
public: //members
    GLFWwindow* m_Window = nullptr;
    ShadersProgram m_Shader;
    std::shared_ptr<VertexBuffer> v_Buff;
    std::shared_ptr<VertexLayout> v_Lay;
    bool m_Initialised=false;
};
