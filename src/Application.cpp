#include <Application.h>
Vector3f uOffset(0.0f,0.0f,0.0f);
GLint uOffsetLocation;

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
    //                x     y     z     R     G      B
    float data[] = { 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  0.0f,
                    -0.5f, 0.5f,-0.5f, 0.0f, 1.0f,  0.0f, 
                    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  0.0f,
                     0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f,
                    -0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f,
                     0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  0.0f,
                     0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f,
                    -0.5f,-0.5f,-0.5f, 0.0f, 1.0f,  0.0f};
    // float data[] = {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
    //                  0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    //                  1.0f, -1.0f, 0.0f, 0.0f, 1.0f};

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

void Application::render() {//init on first frame
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    if(m_Initialised==false){
        this->initAll();
        m_Initialised=true;
    }
    //matrix test

    static float AngleInRadians = 0.0f;

    scalex+=translateDelta;
    scaley+=translateDelta;
    if(scalex>=0.1f||scalex<=0){
        translateDelta*=-1;
    }
    AngleInRadians += rotateDelta;
    if ((AngleInRadians >= 1.5708f) || (AngleInRadians <= -1.5708f)) {
        rotateDelta *= -1.0f;
    }
    float Scale = scalex*10;


    float FOV = 90.0f;
    float tanHalfFOV=tanf(ToRadian(FOV/2.0f));
    float f = 1/tanHalfFOV;
    Matrix4f Projection(1.0f,0.0f,0.0f,0.0f,
                        0.0f,1.0f,0.0f,0.0f,
                        0.0f,0.0f,1.0f,0.0f,
                        0.0f,0.0f,0.0f,1.0f);

    Pipeline p;
    p.WorldPos(uOffset);
    p.Scale(scalex*10);
    Matrix4f FinalTransformation=p.GetTrans();
    Matrix4f Result = FinalTransformation*Projection;
    m_Shader.setUniform(Uniform::Offset,Result);
    m_Shader.bindShaders();
    v_Buff->bind();

    //glDrawArrays(GL_TRIANGLES,0,3);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* handler = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
    if(key==GLFW_KEY_UP){
        uOffset.y+=0.05f;
    }
    if(key==GLFW_KEY_DOWN){
        uOffset.y-=0.05f;
    }
    if(key==GLFW_KEY_LEFT){
        uOffset.x-=0.05f;
    }
    if(key==GLFW_KEY_RIGHT){
        uOffset.x+=0.05f;
    }
}

void Application::window_resize(GLFWwindow *window, int width, int height){
    glViewport(0,0,width,height);
}
