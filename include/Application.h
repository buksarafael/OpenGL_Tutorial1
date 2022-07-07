#pragma once
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
class Application
{
public:
    Application()=default;
    Application& operator = (const Application&) = delete;

public:

    bool initialize(const char* window_name,int width,int height);

    void update(const float delta_seconds);
    //^ called from run() function. delta seconds is the ammount of time (in seconds) that passed since the last update() call. First call has 0 as argument.

    void render();
//    ^ called from run() function.
public:
    void run();
    //^ this functions keeps the application alive until user presses escape

private:
    static void key_callback(GLFWwindow*, int, int, int, int);
    static void window_resize(GLFWwindow* window,int width,int height);
public:
    GLFWwindow* m_Window;
    GLuint vbo;
    //add members here:
};
