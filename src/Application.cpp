#include <Application.h>

bool Application::initialize(const char* window_name, int width, int height){

    //initializing window and context
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
    glfwSetWindowSizeCallback(m_Window, window_resize);
    return true;
}

void Application::initShaders(){
    const char* pVSFileName = "/Users/rafaelb/Desktop/Tutorial1/src/shader.vs";
    const char* pFSFileName = "/Users/rafaelb/Desktop/Tutorial1/src/shader.fs";

    ShadersProgram shader;
    std::array <const char*,2> files={pVSFileName,pFSFileName};
    shader.create(files);
}

void Application::initVertex(){
    v_Lay = std::make_shared<VertexLayout>();
    v_Buff = std::make_shared<VertexBuffer>();

    v_Lay->AddVertexAttribute(AttributeHelper::kPosition, 2);
    v_Lay->AddVertexAttribute(AttributeHelper::kColor, 3);
    //                x      y     R    G     B
    float data[] = {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
                     0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
                     1.0f, -1.0f, 0.0f, 0.0f, 1.0f};

    v_Buff->create(data, *v_Lay, sizeof(data) / v_Lay->size());
    v_Buff->bind();
}

void Application::run(){
    float delta_time = glfwGetTime();

    while (!glfwWindowShouldClose(m_Window))
    {
        float now_time = glfwGetTime();
        this->update(now_time - delta_time);
        this->render();
        delta_time = now_time;

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::update(const float delta_seconds)
{
    //std::cout << delta_seconds << std::endl;
}

void Application::render() {//init on first frame
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    if(m_Initialised==false){
        this->initVertex();
        this->initShaders();
        m_Initialised=true;
    }
    v_Buff->bind();
    glDrawArrays(GL_TRIANGLES,0,3);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* handler = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
}

void Application::window_resize(GLFWwindow *window, int width, int height){
    glViewport(0,0,width,height);
}
