#include <Application.h>
Texture* pTexture=NULL;
GLuint gSamplerLocation;
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
    const char* pVSFileName = "/Users/rafaelb/Desktop/Tutorial1/shaders/shader.vs";
    const char* pFSFileName = "/Users/rafaelb/Desktop/Tutorial1/shaders/shader.fs";
    std::array <const char*,2> files={pVSFileName,pFSFileName};
    m_Shader.create(files);
}

void Application::initVertex(){
    m_VertexLayout = std::make_shared<VertexLayout>();
    m_VertexBuffer = std::make_shared<VertexBuffer>();
    m_IndexBuffer  = std::make_shared<IndexBuffer>();
    

    m_VertexLayout->AddVertexAttribute(AttributeHelper::kPosition, 3);
    m_VertexLayout->AddVertexAttribute(AttributeHelper::kColor, 2);

//                           x     y     z     R     G      B
    // float vertex_data[] = { 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    //                        -0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 
    //                        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    //                         0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
    //                        -0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
    //                         0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 1.0f,
    //                         0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    //                        -0.5f,-0.5f, 0.5f, 0.0f, 1.0f, 0.0f
    // };
    float vertex_data[] = {0.5f, 0.5f, 0.5f, 0.0f, 0.0f,   //0 gata
                           -0.5f, 0.5f,-0.5f, 0.0f, 1.0f,  //1 gata
                           -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  //2 gata
                            0.5f,-0.5f,-0.5f, 1.0f, 1.0f,  //3 gata
                           -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,  //4 gata
                            0.5f, 0.5f,-0.5f, 1.0f, 0.0f,  //5 gata
                            0.5f,-0.5f, 0.5f, 0.0f, 1.0f,  //6
                           -0.5f,-0.5f, 0.5f, 1.0f, 1.0f}; //7

//     static const GLfloat data[] = {
//     -1.0f,-1.0f,-1.0f,1.0f, 0.0f,  0.0f, // triangle 1 : begin
//     -1.0f,-1.0f, 1.0f,0.0f, 1.0f,  0.0f,
//     -1.0f, 1.0f, 1.0f,0.0f, 0.0f,  1.0f, // triangle 1 : end
//     1.0f, 1.0f,-1.0f,1.0f, 0.0f,  0.0f, // triangle 2 : begin
//     -1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
//     -1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f, // triangle 2 : end
//     1.0f,-1.0f, 1.0f,1.0f, 0.0f,  0.0f,
//     -1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
//     1.0f,-1.0f,-1.0f,0.0f, 0.0f,  1.0f,
//     1.0f, 1.0f,-1.0f,1.0f, 0.0f,  0.0f,
//     1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
//     -1.0f,-1.0f,-1.0f,0.0f, 0.0f,  1.0f,
//     -1.0f,-1.0f,-1.0f,1.0f, 0.0f,  0.0f,
//     -1.0f, 1.0f, 1.0f,0.0f, 1.0f,  0.0f,
//     -1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f,
//     1.0f,-1.0f, 1.0f,1.0f, 0.0f,  0.0f,
//     -1.0f,-1.0f, 1.0f,0.0f, 1.0f,  0.0f,
//     -1.0f,-1.0f,-1.0f,0.0f, 0.0f,  1.0f,
//     -1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
//     -1.0f,-1.0f, 1.0f,0.0f, 1.0f,  0.0f,
//     1.0f,-1.0f, 1.0f,0.0f, 0.0f,  1.0f,
//     1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
//     1.0f,-1.0f,-1.0f,0.0f, 1.0f,  0.0f,
//     1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f,
//     1.0f,-1.0f,-1.0f,1.0f, 0.0f,  0.0f,
//     1.0f, 1.0f, 1.0f,0.0f, 1.0f,  0.0f,
//     1.0f,-1.0f, 1.0f,0.0f, 0.0f,  1.0f,
//     1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
//     1.0f, 1.0f,-1.0f,0.0f, 1.0f,  0.0f,
//     -1.0f, 1.0f,-1.0f,0.0f, 0.0f,  1.0f,
//     1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
//     -1.0f, 1.0f,-1.0f,0.0f, 1.0f,  0.0f,
//     -1.0f, 1.0f, 1.0f,0.0f, 0.0f,  1.0f,
//     1.0f, 1.0f, 1.0f,1.0f, 0.0f,  0.0f,
//     -1.0f, 1.0f, 1.0f,0.0f, 1.0f,  0.0f,
//     1.0f,-1.0f, 1.0f,0.0f, 0.0f,  1.0f,
// };

    m_VertexBuffer->create(vertex_data, *m_VertexLayout, sizeof(vertex_data) / m_VertexLayout->size());
    m_VertexBuffer->bind();

    unsigned int index_data[]={0, 1, 2,
                              1, 3, 4,
                              5, 6, 3,
                              7, 3, 6,
                              2, 4, 7,
                              0, 7, 6,
                              0, 5, 1, 
                              1, 5, 3, 
                              5, 0, 6, 
                              7, 4, 3,
                              2, 1, 4, 
                              0, 2, 7
                              };

    m_IndexBuffer->create(*m_VertexBuffer,index_data,sizeof(index_data));
    m_IndexBuffer->bind();
}

void Application::run(){
    float delta_time = glfwGetTime();
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    pTexture=new Texture(GL_TEXTURE_2D,"/Users/rafaelb/Desktop/Tutorial1/assets/bricks.jpeg");
    if(!pTexture->load()){
        exit(200);
    }
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
    Matrix4f FinalMatrix=ProjectionMatrix*ViewMatrix;//*ModelMatrix;
    m_Shader.setUniform(Uniform::uOffset,FinalMatrix);

    pTexture->bind(GL_TEXTURE0);
    glUniform1i(gSamplerLocation,0);
    
    m_Shader.bindShaders();
    m_VertexBuffer->bind();

    //glDrawArrays(GL_TRIANGLES,0,12*3);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* handler = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
    handler->m_Camera.Move(handler->m_Camera.OnKeyboard(key,handler->m_Camera.getPosition(),handler->m_Camera.getTarget()));
}
