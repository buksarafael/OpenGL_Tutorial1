#include <Application.h>
// Vector3f uOffset(0.0f,0.0f,0.0f);
// GLint uOffsetLocation;
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
    return true;
}

void Application::initAll(){
    this->initVertex();
    this->initShaders();
}
void Application::initShaders(){
    const char* pVSFileName = "/Users/rafaelb/Desktop/Tutorial1/src/shader.vs";
    const char* pFSFileName = "/Users/rafaelb/Desktop/Tutorial1/src/shader.fs";
    std::array <const char*,2> files={pVSFileName,pFSFileName};
    m_Shader.create(files);
}

void Application::initVertex(){
    v_Lay = std::make_shared<VertexLayout>();
    v_Buff = std::make_shared<VertexBuffer>();

    v_Lay->AddVertexAttribute(AttributeHelper::kPosition, 3);
    v_Lay->AddVertexAttribute(AttributeHelper::kColor, 3);

//                    x     y     z     R     G      B
    // float data[] = { 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  0.0f,
    //                 -0.5f, 0.5f,-0.5f, 0.0f, 1.0f,  0.0f, 
    //                 -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  1.0f,
    //                  0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f,
    //                 -0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f,
    //                  0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  0.0f,
    //                  0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f,
    //                 -0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f};

    static const GLfloat data[] = {
    -1.0f,-1.0f,-1.0f,1.0f, 0.0f,  0.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,0.0f, 1.0f,  0.0f,
    -1.0f, 1.0f, 1.0f,0.0f, 0.0f,  1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f,1.0f, 0.0f,  0.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
    -1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,1.0f, 0.0f,  0.0f,
    -1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
    1.0f,-1.0f,-1.0f,0.0f, 0.0f,  1.0f,
    1.0f, 1.0f,-1.0f,1.0f, 0.0f,  0.0f,
    1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
    -1.0f,-1.0f,-1.0f,0.0f, 0.0f,  1.0f,
    -1.0f,-1.0f,-1.0f,1.0f, 0.0f,  0.0f,
    -1.0f, 1.0f, 1.0f,0.0f, 1.0f,  0.0f,
    -1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f,
    1.0f,-1.0f, 1.0f,1.0f, 0.0f,  0.0f,
    -1.0f,-1.0f, 1.0f,0.0f, 1.0f,  0.0f,
    -1.0f,-1.0f,-1.0f,0.0f, 0.0f,  1.0f,
    -1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
    -1.0f,-1.0f, 1.0f,0.0f, 1.0f,  0.0f,
    1.0f,-1.0f, 1.0f,0.0f, 0.0f,  1.0f,
    1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
    1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
    1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f,
    1.0f,-1.0f,-1.0f,1.0f, 0.0f,  0.0f,
    1.0f, 1.0f, 1.0f,0.0f, 1.0f,  0.0f,
    1.0f,-1.0f, 1.0f,0.0f, 0.0f,  1.0f,
    1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
    1.0f, 1.0f,-1.0f,0.0f, 1.0f,  0.0f,
    -1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f,
    1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
    -1.0f, 1.0f,-1.0f,0.0f, 1.0f,  0.0f,
    -1.0f, 1.0f, 1.0f,0.0f, 0.0f,  1.0f,
    1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
    -1.0f, 1.0f, 1.0f,0.0f, 1.0f,  0.0f,
    1.0f,-1.0f, 1.0f,0.0f, 0.0f,  1.0f,
};

    v_Buff->create(data, *v_Lay, sizeof(data) / v_Lay->size());
    v_Buff->bind();
}

void Application::run(){
    float delta_time = glfwGetTime();
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
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
float scalex=0;
float scaley=0;
float translateDelta=0.005f;
float rotateDelta=0.01f;
float AngleInRadians = 0.0f;

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    if(m_Initialised==false){ 
        this->initAll();
        m_Initialised=true;
    }
    glfwGetFramebufferSize(m_Window,&m_Width,&m_Height);
    glViewport(0,0,m_Width,m_Height);

    //transform
    static float Scale=2.0f;
    static Pipeline p;
    p.SetWorldPos(0.0f,0.0f,4.0f);
    p.Rotate(0,Scale,0);
    
    //camera projection
    PersProjInfo proj;
    proj.FOV=90.0f;
    proj.Width=m_Width;
    proj.Height=m_Height;
    proj.zNear=0.0f;
    proj.zFar=100.0f;
    m_Camera.setProjection(proj);
    

    //Setting Uniform
    Matrix4f ModelMatrix=p.GetTrans();
    Matrix4f ProjectionMatrix=m_Camera.getProjectionMatrix();
    Matrix4f ViewMatrix=m_Camera.getViewMatrix();
    Matrix4f FinalMatrix=ProjectionMatrix*ViewMatrix*ModelMatrix;
    m_Shader.setUniform(Uniform::Offset,FinalMatrix);
    m_Shader.bindShaders();
    v_Buff->bind();

    glDrawArrays(GL_TRIANGLES,0,12*3);
    //glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* handler = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
    handler->m_Camera.OnKeyboard(key);
}