#include <Engine.h>
bool Engine::initialize(const char* window_name,int width,int height){
    if(!initWindow(window_name,width,height)){
        std::cout<<"Failed to initialize window!"<<std::endl;
    }
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    initBuffer();
    initShaders();
    initCamera();
    initModel();
    initTexture();

    return true;
}

void Engine::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f,0.3f,0.3f,1.0f);

    glfwGetFramebufferSize(m_Window,&m_Width,&m_Height);
    glViewport(0,0,m_Width,m_Height);
    m_Camera.UpdatePerspective(m_Width, m_Height);
    
    auto mvp=m_Camera.getProjectionMatrix()*m_Camera.getViewMatrix()*m_Model.GetTrans();
    m_Shader->setUniform(Uniform::uOffset,mvp);
    m_Shader->setUniform(Uniform::uTexture,1);
    m_Texture->bind(1);
    m_Shader->bindShaders();
    m_VertexBuffer->bind();
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}

void Engine::initBuffer(){
    m_VertexLayout=std::make_shared<VertexLayout>();
    m_VertexBuffer=std::make_shared<VertexBuffer>();
    m_IndexBuffer=std::make_shared<IndexBuffer>();

    m_VertexLayout->AddVertexAttribute(AttributeHelper::kPosition, 3);
    m_VertexLayout->AddVertexAttribute(AttributeHelper::kUV, 2);

    float vertex_data[] = {0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 
                           -0.5f, 0.5f,-0.5f, 0.0f, 1.0f,
                           -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                            0.5f,-0.5f,-0.5f, 1.0f, 1.0f,
                           -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
                            0.5f, 0.5f,-0.5f, 1.0f, 0.0f,
                            0.5f,-0.5f, 0.5f, 0.0f, 1.0f,  
                           -0.5f,-0.5f, 0.5f, 1.0f, 1.0f
        
    };
    m_VertexBuffer->create(vertex_data,*m_VertexLayout,sizeof(vertex_data)/m_VertexLayout->size());
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
                              0, 2, 7};
    m_IndexBuffer->create(*m_VertexBuffer,index_data,sizeof(index_data));
    m_IndexBuffer->bind();
}

void Engine::initShaders(){
    m_Shader=getResourceManager().createShader("shader");
}
void Engine::initTexture(){
    m_Texture = getResourceManager().getTexture("bricks.jpeg");
    m_Texture->load();
    m_Texture->bind(0);
}

void Engine::initCamera(){
    m_Camera.setProjection(m_Width,m_Height);
    m_Camera.LookAt(Vector3f(0.0f,0.0f,4.0f), m_Camera.getPosition());
}

void Engine::initModel(){
    m_Model.SetWorldPos(0.0f,0.0f,4.0f);
}
void Engine::window_callback(Application *App,int Width,int Height){
    Engine *handler = reinterpret_cast<Engine *>(App);
    handler->m_Camera.setProjection(Width,Height);
}
void Engine::key_callback(Application *App, int key){
    Engine *handler = reinterpret_cast<Engine *>(App);
    handler->m_Camera.Move(handler->m_Camera.OnKeyboard(key,handler->m_Camera.getPosition(),handler->m_Camera.getTarget()));
}
ResourceManager &Engine::getResourceManager(){
    return m_ResourceManager;
}
