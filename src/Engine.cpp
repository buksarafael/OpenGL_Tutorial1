#include <Engine.h>
#include <RenderPacket.h>

bool Engine::initialize(const char* window_name,std::size_t width,std::size_t height){
    if(!initWindow(window_name,width,height)){
        std::cout<<"Failed to initialize window!"<<std::endl;
        return false;
    }
    
    initCamera();
    initModel();
    initTerrain();

    m_Mouse.x=0.0f;
    m_Mouse.y=0.0f;

    return true;
}

void Engine::render(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glfwGetFramebufferSize(m_Window,&m_Width,&m_Height);
    glViewport(0,0,m_Width,m_Height);
    
    
    
    m_Camera.setProjection(m_Width,m_Height);
    m_Camera.updateCamera();
    
    m_Terrain->createRenderPackets(m_RenderQueue,m_Camera);
    m_RenderQueue.draw_all();
    m_RenderQueue.clear();

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout<<err<<std::endl;
    }
    //std::cout<<"end of log"<<std::endl;
}

void Engine::update(const InputState &input_state, const float delta_seconds){
    if(input_state.mouse_moved){
        const float yaw_diff=input_state.mouse_delta.x;
        const float pitch_diff = input_state.mouse_delta.y;

        m_Camera.onYaw(yaw_diff * delta_seconds);
        m_Camera.onPitch(pitch_diff * delta_seconds);
    }
    float speed=1.0f;
    if(m_InputState.keys_pressed[GLFW_KEY_LEFT_SHIFT]){
        speed=5.0f;
    }
    if (m_InputState.keys_pressed[GLFW_KEY_W]) {
        m_Camera.moveForward(-delta_seconds*speed);
    }
    if (m_InputState.keys_pressed[GLFW_KEY_S]) {
        m_Camera.moveForward(delta_seconds*speed);
    }
    if (m_InputState.keys_pressed[GLFW_KEY_A]) {
        m_Camera.moveSide(-delta_seconds*speed);
    }
    if (m_InputState.keys_pressed[GLFW_KEY_D]) {
        m_Camera.moveSide(delta_seconds*speed);
    }
    if (m_InputState.keys_pressed[GLFW_KEY_Q]) {
        m_Camera.moveUp(delta_seconds*speed*2.0f);
    }
    if (m_InputState.keys_pressed[GLFW_KEY_E]) {
        m_Camera.moveUp(-delta_seconds*speed*2.0f);
    }
    if(m_InputState.keys_pressed[GLFW_KEY_G]){
        initTerrain();
    }
}

void Engine::initTerrain(){
    m_HeightMap = getResourceManager().getHeightMap("heightmap.tga");

    m_Terrain = std::make_shared<Terrain>();
    m_Terrain->initResources(&getResourceManager());
    m_Terrain->loadHeightMap(m_HeightMap);
    m_Terrain->generate();
}

void Engine::initCamera(){
    m_Camera.setProjection(m_Width,m_Height);
    //_Camera.LookAt(0.0f,0.0f,0.0f);
}

void Engine::initModel(){
    m_Model.SetWorldPos(0.0f,0.0f,4.0f);
}
void Engine::window_callback(int Width,int Height){
    Application::window_callback(Width,Height);
    this->m_Camera.setProjection((float)Width,(float)Height);
}
void Engine::before_run(InputState &input_state){
    capture_mouse();
}
