#include <Application.h>

bool Application::initialize(const char* window_name, int width, int height)
{

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
    
    //vertices stuff

    VertexLayout* vlayout = new VertexLayout;
    VertexBuffer* vbuffer = new VertexBuffer;

    vlayout->AddVertexAttribute("pos",2);

    float data[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    vbuffer->create(data,*vlayout,sizeof(data)/vlayout->size());
    vbuffer->bind();
    this.configure_shaders();
    m_Shaders.use_shaders();


    //Vector3f Vertices[3];
    //Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    //Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    //Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
    //glGenBuffers(1, &vbo);                                                     //generate buffer object names
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);                                        //binds the vbo to the buffer array
    //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //

    return true;
}

void Application::run()
{
    float delta_time = glfwGetTime();

    while (!glfwWindowShouldClose(m_Window))
    {
        float now_time = glfwGetTime();

        this->update(now_time - delta_time);
        //glfwMakeContextCurrent(m_Window);
        this->render();
        delta_time = now_time;

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::update(const float delta_seconds)
{
    std::cout << delta_seconds << std::endl;
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
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
