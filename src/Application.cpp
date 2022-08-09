#include <Application.h>

bool Application::initWindow(const char* window_name, std::size_t width, std::size_t height){

    if (!glfwInit()){
        std::cout<<"Failed to initialize GLFW";
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_Window = glfwCreateWindow(width, height, window_name, NULL, NULL);

    if (!m_Window)
    {
        std::cout<<"Failed to initialize window"<<std::endl;
        glfwTerminate();
        return false;
    }
    else{
        std::cout<<"Created window!"<<std::endl;
    }
    
    glfwMakeContextCurrent(m_Window);
    glfwSetKeyCallback(m_Window, Application::key_callback);
    glfwSetWindowUserPointer(m_Window, this);
    return true;
}

void Application::run(){
    float delta_time = glfwGetTime();
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    while(!glfwWindowShouldClose(m_Window)){
        this->render();
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

float Application::getWidth() const{
    return m_Width;
}

float Application::getHeight() const{
    return m_Height;
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* handler = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
    handler->key_callback(handler,key);
    }
